#pragma once

enum class GameState { MAIN_MENU, CUTSCENE, PLAYING, PAUSED, WON, LOST };
extern GameState gameState;

void renderGame();
void drawGameScreen();
void onKey(int key);
void onClick(float mouseX, float mouseY);
bool loadInfinityGuantlet();
void drawInfinityGuantlet(float x, float y, float w, float h);
void cleanupGame();
void update(float deltaTime);   

//for game logic
float laneCenter(int lane);
void spawnEnemy(int lane);
void spawnEasyEnemy(int lane);
void spawnHardEnemy(int lane);
void spawnMediumEnemy(int lane);
extern int hoverLane;
extern int hoverCard;
int whatLane(float mouseX, float mouseY);