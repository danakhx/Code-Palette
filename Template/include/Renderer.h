#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

void initRenderer();
void clearScreen();
void drawRect(float x, float y, float w, float h, const glm::vec4& color);
void drawTriangle(float x, float y, float w, float h, const glm::vec4& color);
void cleanupRenderer();
