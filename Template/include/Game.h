#pragma once
#include <vector>
#include <array>

enum class GameState { MAIN_MENU, CUTSCENE, PLAYING, PAUSED, WON, LOST };
extern GameState gameState;
extern int hoverLane;
extern std::array<bool, 4> selectedLanes;// 4 lanes bcuz lane 123 w 0 unuseddd
extern int points;
extern int wave;

//for 3amatan
void renderGame();
void onKey(int key);
void onClick(float mouseX, float mouseY);
void cleanupGame();
void update(float deltaTime);   

//for game logic
float laneCenter(int lane);
void spawnEnemy(int lane);
void spawnEasyEnemy(int lane);
void spawnHardEnemy(int lane);
void spawnMediumEnemy(int lane);
int whatLane(float mouseX, float mouseY);
void restartGame();
int maxCount(int w);
void updateShop(int cpoints);
int randomLane();
float HPscale(int currentHP, int maxHP);

struct impactEffect {
    int lane;
    float x;
    float y;
    float timer;
};