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
    drawRect(0, 500,1280, 220, glm::vec4(0.000f, 0.137f, 0.369f, 1.0f)); //sky
    drawRect(0, 0, 1280,300, glm::vec4(0.620f, 0.620f, 0.620f, 1.0f)); //street
    drawRect(0.0f, 300.0f, 1280.0f, 25.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f)); //sidewalk
    //street lines
    drawRect(0.0f, 160.0f, 200.0f, 20.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f)); 
    drawRect(350.0f, 160.0f, 200.0f, 20.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f)); 
    drawRect(700.0f, 160.0f, 200.0f, 20.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f)); 
    drawRect(1050.0f, 160.0f, 200.0f, 20.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f)); 
    //buildings
    drawRect(0,325, 180, 300, glm::vec4(0.690f, 0.745f, 0.773f, 1.0f));
    drawRect(180,325, 180, 420, glm::vec4(0.471f, 0.565f, 0.612f, 1.0f));
    drawRect(360,325, 180, 260, glm::vec4(0.271f, 0.353f, 0.392f, 1.0f));
    drawRect(540,325, 180, 320, glm::vec4(0.690f, 0.745f, 0.773f, 1.0f));
    drawRect(720,325, 180, 420, glm::vec4(0.471f, 0.565f, 0.612f, 1.0f));
    drawRect(900,325, 180, 370,glm::vec4(0.271f, 0.353f, 0.392f, 1.0f));
    drawRect(1080,325, 180, 290, glm::vec4(0.690f, 0.745f, 0.773f, 1.0f));
    drawRect(1260,325, 180, 420, glm::vec4(0.471f, 0.565f, 0.612f, 1.0f));
    //drawRect(0,325, 180, 300, glm::vec4(0.271f, 0.353f, 0.392f, 1.0f));

    //shade
    drawRect(0,0,1280,720, glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)); 
    //loki
    drawRect(100, 380, 200, 80, glm::vec4(1, 1, 1, 1.));
    drawTextCentered("Welcome back, Avenger!", 100, 380, 200, 80, 1.5f, glm::vec4(0, 0, 0, 1));
    drawTriangle(185, 380, 30, -25, glm::vec4(1,1,1,1));
    drawLoki(0, 100, 400, 400);
    //end of loki
    drawText("Avengers Assemble!", 395, 550, 5.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 390.0f, 500.0f, 100.0f, glm::vec4(0.106f, 0.369f, 0.125f, 1.0f)); //start button
    drawText("Start", 610, 445, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 270.0f, 500.0f, 100.0f, glm::vec4(0.290f, 0.078f, 0.549f, 1.0f)); //audio button (bonus remove if no time)
    drawText("Sound", 600, 325, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 150.0f, 500.0f, 100.0f, glm::vec4(0.533f, 0.055f, 0.310f, 1.0f)); //exit button
    drawText("Exit", 610, 205, 3.0f, glm::vec4(1, 1, 1, 1));
 }

 void drawPauseScreen(){
    drawTextCentered("Game Paused", 0, 550, 1280, 50, 5.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 390.0f, 500.0f, 100.0f, glm::vec4(0.106f, 0.369f, 0.125f, 1.0f)); //continue button
    drawTextCentered("Continue", 390, 390, 500, 100, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 270.0f, 500.0f, 100.0f, glm::vec4(0.290f, 0.078f, 0.549f, 1.0f)); //restart button
    drawTextCentered("Restart", 390, 270, 500, 100, 3.0f, glm::vec4(1, 1, 1, 1));
    drawRect(390.0f, 150.0f, 500.0f, 100.0f, glm::vec4(0.533f, 0.055f, 0.310f, 1.0f)); //return button
    drawTextCentered("Return to Main Menu", 390, 150, 500, 100, 3.0f, glm::vec4(1, 1, 1, 1));
 }