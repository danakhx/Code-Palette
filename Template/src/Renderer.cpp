#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

#include "charactersload.h"
#include <iostream>
#include "stb_easy_font.h"
#include <vector>
#include "UI.h"

static GLuint shader = 0;
static GLuint characterShader = 0;// id shader prog char
static GLuint triVAO = 0, triVBO = 0;
static GLuint rectVAO = 0, rectVBO = 0;
static GLuint textVAO = 0, textVBO = 0;
static GLuint characterVAO = 0;
static GLuint characterVBO = 0;
static GLuint characterTexture = 0;
static GLuint crouchTexture = 0;
static GLuint lokiTexture = 0;
static GLuint guantletTexture = 0;
static bool isCrouching = false;

//cap run and fight
static GLuint crunTexture = 0;
static GLuint cfightTexture = 0;
static GLuint cjumpTex=0;
static GLuint ccrouchTex=0;
// this is caps animation frames ashan msh divided helw had to have them csalculated
struct SpriteFrame {
    float uStart;
    float uEnd;
};
// ustart u end variabels
static const SpriteFrame capFightFrames[] = {
    {0.00153f, 0.13936f}, // Frame 1
    {0.14242f, 0.34609f}, // Frame 2
    {0.34916f, 0.56355f}, // Frame 3
    {0.56662f, 0.78101f}, // Frame 4
    {0.78407f, 0.99847f}  // Frame 5
};


//hulk texture
static GLuint hulktex=0;

// ashrar
static GLuint ttex=0;
static GLuint dtex=0;
static GLuint mtex=0;


// spidermn web
static GLuint WebTexture = 0;
static GLuint impactTexture = 0;


static const char* vertexShaderSource = R"(
#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
}
)";

static const char* fragmentShaderSource = R"(
#version 410 core
out vec4 FragColor;

uniform vec4 color;

void main()
{
    FragColor = color;
}
)";

// shader for el texture char

static const char* charvertexShaderSource =R"(
#version 410 core 
layout (location = 0) in vec3 aPos;
layout (location=1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";


static const char* chartextureFragmentShaderSource = R"(
#version 410 core
in vec2 TexCoord;
uniform sampler2D characterTexture;
out vec4 FragColor;
void main()
{
    FragColor = texture(characterTexture,TexCoord);
}
)";









GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compile error:\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint createShaderProgram() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader link error:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint newtextureShaderProgram(){
    GLuint textureVertexShaderSource = compileShader(GL_VERTEX_SHADER, charvertexShaderSource);
    GLuint textureFragmentShaderSource=compileShader(GL_FRAGMENT_SHADER, chartextureFragmentShaderSource);
    GLuint textureshaderProgram = glCreateProgram();
    glAttachShader(textureshaderProgram, textureVertexShaderSource);
    glAttachShader(textureshaderProgram, textureFragmentShaderSource);
    glLinkProgram(textureshaderProgram);
    

    int success=0;
    glGetProgramiv(textureshaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(textureshaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader link error:\n" << infoLog << std::endl;
    }



    glDeleteShader(textureVertexShaderSource);
    glDeleteShader(textureFragmentShaderSource);

    return textureshaderProgram;
}

void setCrouching(bool crouching)
{
    isCrouching = crouching;
}

void initRenderer() {
    shader = createShaderProgram();
    characterShader = newtextureShaderProgram();
    characterTexture = characterstextures(SPstand);
    crouchTexture = characterstextures(SPcrouch);
    glGenVertexArrays(1, &textVAO);glGenBuffers(1, &textVBO);glBindVertexArray(textVAO);glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    lokiTexture = characterstextures(Loki);
    guantletTexture = characterstextures(infinityGuantlet);
    //cap
    crunTexture = characterstextures(Cap);
    cfightTexture = characterstextures(Capfight);
    cjumpTex=characterstextures(Cjump);
    ccrouchTex=characterstextures(Ccrouch);
    hulktex=characterstextures(hulk);

    WebTexture =characterstextures(web);
    impactTexture = characterstextures(webimpact);


    //ayo initilatzaton
    // Enemy textures
    dtex = characterstextures(doom);
    mtex = characterstextures(magneto);
    ttex = characterstextures(thanos);


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
    glDeleteTextures(1, &crouchTexture);
    glDeleteTextures(1, &lokiTexture);
    glDeleteTextures(1, &guantletTexture);

    glDeleteTextures(1, &crunTexture);
    glDeleteTextures(1, &cfightTexture);
    glDeleteTextures(1,&cjumpTex);
    glDeleteTextures(1,&ccrouchTex);
    
    glDeleteTextures(1,&hulktex);

    glDeleteTextures(1,&mtex);
    glDeleteTextures(1,&dtex);
    glDeleteTextures(1,&ttex);       
    
    glDeleteTextures(1,&WebTexture);
    glDeleteTextures(1,&impactTexture);


}

//characters  texture eftkery takes el image data  uploads it ka texture

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
    GLuint currentTexture = isCrouching ? crouchTexture : characterTexture;
    glBindTexture(GL_TEXTURE_2D, currentTexture);
    glBindVertexArray(characterVAO);
    
    GLuint x=glGetUniformLocation(characterShader,"characterTexture");
    glUniform1i(x,0);

    glUniformMatrix4fv(glGetUniformLocation(characterShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    
}
//general drawing sprite function might be better badal function le kol character
// using it for loki anyway
void drawSprite(GLuint texture, float x, float y, float w, float h){
    glUseProgram(characterShader);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(w, h, 1.0f));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(characterShader, "characterTexture"), 0);
    glUniformMatrix4fv(glGetUniformLocation(characterShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(characterVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
void drawLoki(float x, float y, float w, float h){
    drawSprite(lokiTexture, x, y, w, h);
}
void drawInfinityGuantlet(float x, float y, float w, float h){
    drawSprite(guantletTexture, x, y, w, h);

}
void drawProjectile(float x, float y, glm::vec4 color){
    drawRect(x,y,20,5,color);
}


// we need this le captan maerica ashan howa sprite sheet 
void drawSpriteFrame(GLuint texture, float x, float y, float w, float h, int frameIndex) {

    //3ashan manst3mlsh frame msh existent
    if (frameIndex < 0 || frameIndex >= 5) {
    return;
}

    // Select the requested frame
    SpriteFrame frame = capFightFrames[frameIndex];

    // Update the texture coordinates
    float frameVertices[] = {
        0, 0, 0, frame.uStart, 0,
        1, 0, 0, frame.uEnd,   0,
        1, 1, 0, frame.uEnd,   1,

        0, 0, 0, frame.uStart, 0,
        1, 1, 0, frame.uEnd,   1,
        0, 1, 0, frame.uStart, 1
    };

    // Update the existing character VBO
    glBindBuffer(GL_ARRAY_BUFFER, characterVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(frameVertices), frameVertices);

    // Position and size
    glUseProgram(characterShader);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(w, h, 1.0f));

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(glGetUniformLocation(characterShader, "characterTexture"), 0);

    glUniformMatrix4fv(
        glGetUniformLocation(characterShader, "model"),
        1, GL_FALSE, glm::value_ptr(model)
    );

    // Draw
    glBindVertexArray(characterVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Restore the original full-texture coordinates
    float originalVertices[] = {
    0, 0, 0, 0, 0,
    1, 0, 0, 1, 0,
    1, 1, 0, 1, 1,

    0, 0, 0, 0, 0,
    1, 1, 0, 1, 1,
    0, 1, 0, 0, 1 };
   
    glBindBuffer(GL_ARRAY_BUFFER, characterVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(originalVertices), originalVertices);


}
// ashan msh nexpose it globally el xture w bas game cpp ely y2raaa



void drawCaptainAmericaFight(float x, float y, float w, float h, int frameIndex) {
    drawSpriteFrame(cfightTexture, x, y, w, h, frameIndex);
}
void drawCaptainAmericaRun(float x, float y, float w, float h) {
    drawSprite(crunTexture, x, y, w, h);
}
void drawCjump(float x, float y, float w, float h){
    drawSprite(cjumpTex, x, y, w, h);

}
void drawCcrouch(float x, float y, float w, float h){
    drawSprite(ccrouchTex, x, y, w, h);
}

void drawmagneto(float x, float y, float w, float h){
     drawSprite(mtex, x, y, w, h);
}
void drawdoom(float x, float y, float w, float h){
     drawSprite(dtex, x, y, w, h);
}
void drawthanos(float x, float y, float w, float h){
     drawSprite(ttex, x, y, w, h);
}

void drawhulk(float x, float y, float w, float h){
    drawSprite(hulktex,x,y,w,h);
}

void drawweb(float x, float y, float w, float h){
    drawSprite(WebTexture,x,y,w,h);
    
}
void drawimpact(float x, float y, float w, float h){
    drawSprite(impactTexture,x,y,w,h);
}