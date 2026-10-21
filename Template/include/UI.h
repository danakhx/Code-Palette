#pragma once
#include "charactersload.h"

struct Button{
    float x, y, w, h;
};

bool isMouseOver(const Button& b, float mx, float my);

extern Button mStart;
extern Button mExit;
extern Button pContinue;
extern Button pRestart;
extern Button pMainMenu;
extern Button player1;
extern Button player2;
extern Button player3;

void drawMainMenu();
void drawPauseScreen();
void drawGameScreen();

extern Pixeldata Loki;
bool loadLoki();

extern Pixeldata infinityGuantlet;

//glm::vec4 laneColor(int lane);

void canAfford(int p);