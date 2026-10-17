#include "UI.h"
#include "Game.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#ifndef ENTITIES_DIR
#define ENTITIES_DIR "Template/src/Entities/"
#endif

Pixeldata Loki;

bool loadLoki(){
    Loki.ppointer=stbi_load(ENTITIES_DIR "loki.png",&Loki.width,&Loki.height,&Loki.channels,0);
    if (Loki.ppointer == nullptr) {
        return false;
    }
    return true;
}

Button mStart    = {390, 390, 500, 100};
Button mExit     = {390, 150, 500, 100};
Button pContinue = {390, 390, 500, 100};
Button pRestart  = {390, 270, 500, 100};
Button pMainMenu = {390, 150, 500, 100};

bool isMouseOver(const Button& b, float mx, float my) {
    return mx >= b.x && mx <= b.x + b.w &&
           my >= b.y && my <= b.y + b.h;
}

void drawMainMenu()   {
    drawRect(100, 380, 200, 80, glm::vec4(1, 1, 1, 1.));
    drawTextCentered("Welcome back, Avenger!", 100, 380, 200, 80, 1.5f, glm::vec4(0, 0, 0, 1));
    drawTriangle(185, 380, 30, -25, glm::vec4(1,1,1,1));
    drawLoki(0, 100, 400, 400);
    drawText("Avengers Assemble!", 395, 550, 5.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 390.0f, 500.0f, 100.0f, glm::vec4(0.2f, 0.6f, 0.2f, 1.0f)); //start button
    drawText("Start", 610, 445, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 270.0f, 500.0f, 100.0f, glm::vec4(0.6f, 0.2f, 0.2f, 1.0f)); //audio button (bonus remove if no time)
    drawText("Sound", 600, 325, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 150.0f, 500.0f, 100.0f, glm::vec4(0.2f, 0.2f, 0.6f, 1.0f)); //exit button
    drawText("Exit", 610, 205, 3.0f, glm::vec4(1, 1, 1, 1));
 }

 void drawPauseScreen(){
    drawTextCentered("Game Paused", 0, 550, 1280, 50, 5.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 390.0f, 500.0f, 100.0f, glm::vec4(0.2f, 0.6f, 0.2f, 1.0f)); //continue button
    drawTextCentered("Continue", 390, 390, 500, 100, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 270.0f, 500.0f, 100.0f, glm::vec4(0.6f, 0.2f, 0.2f, 1.0f)); //restart button
    drawTextCentered("Restart", 390, 270, 500, 100, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 150.0f, 500.0f, 100.0f, glm::vec4(0.2f, 0.2f, 0.6f, 1.0f)); //return button
    drawTextCentered("Return to Main Menu", 390, 150, 500, 100, 3.0f, glm::vec4(1, 1, 1, 1));
 }