#pragma once
#include <glm/glm.hpp>
#include "charactersload.h"

struct GLFWwindow;
extern float mouseX, mouseY;
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
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
void drawWinscreen();
void drawLoseScreen();
void drawGameScreen();
static void Streetlight(float x, float y);
void drawEnvironment();

extern Pixeldata Loki;
bool loadLoki();

extern Pixeldata infinityGuantlet;
bool loadInfinityGuantlet();

glm::vec4 laneColor(int lane);

void canAfford(int p);

//shop related
extern Pixeldata capFace;
extern Pixeldata grayCap;
extern Pixeldata spiderFace;
extern Pixeldata graySpider;
extern Pixeldata hulkFace;
extern Pixeldata grayHulk;
extern Pixeldata pointReactor;

bool loadCapFace();
bool loadGrayCap();
bool loadSpiderFace();
bool loadGraySpider();
bool loadHulkFace();
bool loadGrayHulk();
bool loadPointReactor();
