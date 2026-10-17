#pragma once

struct Button{
    float x, y, w, h;
};

bool isMouseOver(const Button& b, float mx, float my);

extern Button mStart;
extern Button mExit;
extern Button pContinue;
extern Button pRestart;
extern Button pMainMenu;

void drawMainMenu();
void drawPauseScreen();
