#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Shader.h"
#include "charactersload.h"
#include <iostream>
#include "stb_easy_font.h"
#include <vector>

static GLuint shader = 0;
static GLuint characterShader = 0;// id shader prog char
static GLuint triVAO = 0, triVBO = 0;
static GLuint rectVAO = 0, rectVBO = 0;
static GLuint characterVAO = 0;
static GLuint characterVBO = 0;
static GLuint characterTexture = 0;
  
void initRenderer() {
    shader = createShaderProgram();
    characterShader = newtextureShaderProgram();
    characterTexture = characterstextures(SPstand);
    
    // --- Unit shapes (0..1), scaled/moved by the model matrix ---
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

    // vertices bas lel character
    float charVertices[]={
       0,0,0,0,0,
       1,0,0,1,0,
       1,1,0,1,1,
       0,0,0,0,0,
       1,1,0,1,1,
       0,1,0,0,1,                        //xyzuv
    };
    

    glGenVertexArrays(1,&characterVAO);glGenBuffers(1,&characterVBO);
    glBindVertexArray(characterVAO);glBindBuffer(GL_ARRAY_BUFFER,characterVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(charVertices),charVertices,GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);






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


    //char 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(characterShader);
    glUniformMatrix4fv(glGetUniformLocation(characterShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void drawTextCentered(const char* text, float rx, float ry, float rw, float rh,
                      float scale, glm::vec4 color) {
    float tx = rx + (rw - textWidth(text, scale)) / 2.0f;
    float ty = ry + rh / 2.0f + (7.0f * scale) / 2.0f;  
    drawText(text, tx, ty, scale, color);
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
    glDeleteVertexArrays(1, &characterVAO);
    glDeleteBuffers(1, &characterVBO);
    glDeleteTextures(1, &characterTexture);
    glDeleteProgram(characterShader);
    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &textVBO);
}

//characters  texture

GLuint characterstextures(Pixeldata player){
     GLuint textureID=0;
     glGenTextures(1,&textureID);
     glBindTexture(GL_TEXTURE_2D,textureID);
     int x=player.channels;
     if (x==3) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,player.width,player.height,0,GL_RGB,GL_UNSIGNED_BYTE,player.ppointer);
     }
     else{
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,player.width,player.height,0,GL_RGBA,GL_UNSIGNED_BYTE,player.ppointer);
     }

     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

     return textureID;
}


void drawplayer(){
    glUseProgram(characterShader);
    glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(60.0f, 60.0f, 0.0f));

    model = glm::scale(model,glm::vec3(90.0f, 90.0f, 1.0f));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,characterTexture);
    glBindVertexArray(characterVAO);
    
    GLuint x=glGetUniformLocation(characterShader,"characterTexture");
    glUniform1i(x,0);

    glUniformMatrix4fv(glGetUniformLocation(characterShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    
}