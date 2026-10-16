#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Shader.h"
#include "stb_easy_font.h"
#include <vector>

static GLuint shader = 0;
static GLuint triVAO = 0, triVBO = 0;
static GLuint rectVAO = 0, rectVBO = 0;
static GLuint textVAO = 0, textVBO = 0;

void initRenderer() {
    shader = createShaderProgram();

    glGenVertexArrays(1, &textVAO);
glGenBuffers(1, &textVBO);
glBindVertexArray(textVAO);
glBindBuffer(GL_ARRAY_BUFFER, textVBO);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindVertexArray(0);

    float triVertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f
    };

    float rectVertices[] = {
        0.0f, 0.0f, 0.0f,   //  1
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,   //  2
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &triVAO);
    glGenBuffers(1, &triVBO);
    glBindVertexArray(triVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // pixel coordinates, origin bottom-left
    glUseProgram(shader);
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void drawText(const char* text, float x, float y, float scale, glm::vec4 color) {
    static char buffer[60000];   // room for ~200 characters
    int numQuads = stb_easy_font_print(0, 0, (char*)text, nullptr, buffer, sizeof(buffer));

    // convert quads to triangles, keeping only x,y,z
    std::vector<float> verts;
    verts.reserve(numQuads * 18);
    int order[6] = {0, 1, 2, 0, 2, 3};
    for (int q = 0; q < numQuads; q++) {
        for (int k : order) {
            float* v = (float*)(buffer + (q * 4 + k) * 16);  // 16 bytes per vertex
            verts.push_back(v[0]);
            verts.push_back(v[1]);
            verts.push_back(0.0f);
        }
    }

    // position + scale, with Y flipped (stb is Y-down)
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(scale, -scale, 1.0f));

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(verts.size() / 3));
    glBindVertexArray(0);
}

float textWidth(const char* text, float scale) {
    return stb_easy_font_width((char*)text) * scale;
}

void clearScreen() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void drawShape(GLuint vao, GLsizei vertexCount, float x, float y, float w, float h, const glm::vec4& color) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(w, h, 1.0f));

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void drawRect(float x, float y, float w, float h, const glm::vec4& color) {
    drawShape(rectVAO, 6, x, y, w, h, color);
}

void drawTriangle(float x, float y, float w, float h, const glm::vec4& color) {
    drawShape(triVAO, 3, x, y, w, h, color);
}

void cleanupRenderer() {
    glDeleteVertexArrays(1, &triVAO);
    glDeleteBuffers(1, &triVBO);
    glDeleteVertexArrays(1, &rectVAO);
    glDeleteBuffers(1, &rectVBO);
    glDeleteProgram(shader);
    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &textVBO);
}
