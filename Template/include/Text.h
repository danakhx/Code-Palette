#pragma once
#include <string>
#include <glm/glm.hpp>

// Loads the font with FreeType and builds a texture for each ASCII glyph.
// fontSize is the glyph height in pixels at scale 1.0.
bool initText(const char* fontPath, unsigned int fontSize = 48);

// Draws text in pixel coordinates (origin bottom-left, same as drawRect).
// (x, y) is the left end of the baseline.
void drawText(const std::string& text, float x, float y, float scale, const glm::vec4& color);

// Width/height in pixels the text would take at the given scale (for centering).
float textWidth(const std::string& text, float scale);
float textHeight(const std::string& text, float scale);

void cleanupText();
