#include "UI.h"
#include "Game.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


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