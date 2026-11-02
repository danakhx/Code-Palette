#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "charactersload.h"

GLuint compileShader(GLenum type, const char* source);
GLuint createShaderProgram();
GLuint newtextureShaderProgram();

void initRenderer();
void clearScreen();
void drawRect(float x, float y, float w, float h, const glm::vec4& color);
void drawTriangle(float x, float y, float w, float h, const glm::vec4& color);
void cleanupRenderer();
//void drawplayer();
void setCrouching(bool crouching);
void drawSprite(GLuint texture, float x, float y, float w, float h);
void drawLoki(float x, float y, float w, float h);
void drawInfinityGuantlet(float x, float y, float w, float h);

GLuint characterstextures(Pixeldata player);
void drawText(const char* text, float x, float y, float scale, glm::vec4 color);
float textWidth(const char* text, float scale);
void drawTextCentered(const char* text, float rx, float ry, float rw, float rh, float scale, glm::vec4 color);

void drawProjectile(float x, float y, glm::vec4);

void drawSprite(GLuint texture, float x, float y, float w, float h);
void drawCaptainAmericaFight(float x, float y, float w, float h, int frameIndex);
void drawCaptainAmericaRun(float x, float y, float w, float h);
void drawCcrouch(float x, float y, float w, float h);
void drawCjump(float x, float y, float w, float h);
void drawdoom(float x, float y, float w, float h);
void drawthanos(float x, float y, float w, float h);
void drawmagneto(float x, float y, float w, float h);
void drawhulk(float x, float y, float w, float h);
void drawimpact(float x, float y, float w, float h);
void drawweb(float x, float y, float w, float h);

//shop related
void drawcapFace(float x, float y, float w, float h);
void drawgrayCap(float x, float y, float w, float h);
void drawspiderFace(float x, float y, float w, float h);
void drawgraySpider(float x, float y, float w, float h);
void drawhulkFace(float x, float y, float w, float h);
void drawgrayHulk(float x, float y, float w, float h);
void drawpointReactor(float x, float y, float w, float h);
void drawSPstand(float x, float y, float w, float h);
void drawSPcrouch(float x, float y, float w, float h);