#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "charactersload.h"
void initRenderer();
void clearScreen();
void drawRect(float x, float y, float w, float h, const glm::vec4& color);
void drawTriangle(float x, float y, float w, float h, const glm::vec4& color);
void cleanupRenderer();
void drawplayer();

GLuint characterstextures(Pixeldata player);
void drawText(const char* text, float x, float y, float scale, glm::vec4 color);
float textWidth(const char* text, float scale);
void drawTextCentered(const char* text, float rx, float ry, float rw, float rh, float scale, glm::vec4 color);
