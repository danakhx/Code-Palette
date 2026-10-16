#pragma once

enum class GameState { MAIN_MENU, CUTSCENE, PLAYING, PAUSED, WON, LOST };
extern GameState gameState;

void renderGame();
void drawGameScreen();
void onKey(int key);
void onClick(float mouseX, float mouseY);