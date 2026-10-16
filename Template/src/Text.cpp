#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "Text.h"
#include "Shader.h"

// --- Text shader: samples the glyph's red channel as alpha ---
static const char* textVertexSource = R"(
#version 430 core
layout (location = 0) in vec4 vertex; // xy = position, zw = texture coords
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
)";

static const char* textFragmentSource = R"(
#version 430 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D glyph;
uniform vec4 color;

void main()
{
    float alpha = texture(glyph, TexCoords).r;
    FragColor = vec4(color.rgb, color.a * alpha);
}
)";

struct Glyph {
    GLuint texture;
    glm::ivec2 size;      // bitmap size in pixels
    glm::ivec2 bearing;   // offset from the pen position to the bitmap's top-left
    unsigned int advance; // distance to the next glyph, in 1/64 pixels
};

static Glyph glyphs[128];
static GLuint textShader = 0;
static GLuint textVAO = 0, textVBO = 0;

bool initText(const char* fontPath, unsigned int fontSize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Failed to init FreeType\n";
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        std::cerr << "Failed to load font: " << fontPath << "\n";
        FT_Done_FreeType(ft);
        return false;
    }
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    // Glyph bitmaps are 1 byte per pixel, so rows aren't 4-byte aligned
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "Failed to load glyph " << (int)c << "\n";
            glyphs[c] = {};
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glyphs[c] = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // --- One dynamic quad (6 vertices of vec4), refilled per glyph ---
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // --- Same pixel projection as the renderer ---
    textShader = createShaderProgram(textVertexSource, textFragmentSource);
    glUseProgram(textShader);
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(textShader, "glyph"), 0);

    // Glyph edges are anti-aliased via alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void drawText(const std::string& text, float x, float y, float scale, const glm::vec4& color) {
    glUseProgram(textShader);
    glUniform4fv(glGetUniformLocation(textShader, "color"), 1, glm::value_ptr(color));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);

    for (unsigned char c : text) {
        if (c >= 128) continue;
        const Glyph& g = glyphs[c];

        float xpos = x + g.bearing.x * scale;
        float ypos = y - (g.size.y - g.bearing.y) * scale;
        float w = g.size.x * scale;
        float h = g.size.y * scale;

        // Bitmap rows start at the top, so v is flipped
        float vertices[6][4] = {
            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos,     ypos,     0.0f, 1.0f },
            { xpos + w, ypos,     1.0f, 1.0f },
            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos + w, ypos,     1.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 0.0f }
        };

        if (g.texture) {
            glBindTexture(GL_TEXTURE_2D, g.texture);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        x += (g.advance >> 6) * scale; // advance is in 1/64 pixels
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

float textWidth(const std::string& text, float scale) {
    float width = 0.0f;
    for (unsigned char c : text) {
        if (c < 128) width += (glyphs[c].advance >> 6) * scale;
    }
    return width;
}

float textHeight(const std::string& text, float scale) {
    float height = 0.0f;
    for (unsigned char c : text) {
        if (c < 128 && glyphs[c].bearing.y * scale > height) height = glyphs[c].bearing.y * scale;
    }
    return height;
}

void cleanupText() {
    for (Glyph& g : glyphs) {
        if (g.texture) glDeleteTextures(1, &g.texture);
        g.texture = 0;
    }
    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &textVBO);
    glDeleteProgram(textShader);
}
