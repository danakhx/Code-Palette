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
Pixeldata infinityGuantlet;

//shop and points
Pixeldata capFace;
Pixeldata grayCap;
Pixeldata spiderFace;
Pixeldata graySpider;
Pixeldata hulkFace;
Pixeldata grayHulk;
Pixeldata pointReactor;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        onKey(key);   // in game.cpp
    }
}
//MOUSE STUFF
float mouseX=0, mouseY=0;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
  mouseX= xpos;
  mouseY=720.0f-ypos;

}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        mouse_callback(window, xpos, ypos);
        onClick(mouseX, mouseY); //also in game.cpp
    }
}
bool isMouseOver(const Button& b, float mx, float my) {
    return mx >= b.x && mx <= b.x + b.w &&
           my >= b.y && my <= b.y + b.h;
}


 bool loadInfinityGuantlet(){
    infinityGuantlet.ppointer= stbi_load(ENTITIES_DIR "infinityGuantlet.png",
    &infinityGuantlet.width, &infinityGuantlet.height, &infinityGuantlet.channels,0);
        if(infinityGuantlet.ppointer == nullptr){
            return false;
        }
        return true;
}
bool loadLoki(){
    Loki.ppointer=stbi_load(ENTITIES_DIR "loki.png",&Loki.width,&Loki.height,&Loki.channels,0);
    if (Loki.ppointer == nullptr) {
        return false;
    }
    return true;
}

//load shop
bool loadCapFace(){
    capFace.ppointer=stbi_load(ENTITIES_DIR "capFace.png",&capFace.width,&capFace.height,&capFace.channels,0);
    if (capFace.ppointer == nullptr) {
        return false;
    }
    return true;
}
bool loadGrayCap(){
    grayCap.ppointer=stbi_load(ENTITIES_DIR "grayCap.png",&grayCap.width,&grayCap.height,&grayCap.channels,0);
    if (grayCap.ppointer == nullptr) {
        return false;
    }
    return true;
}
bool loadSpiderFace(){
    spiderFace.ppointer=stbi_load(ENTITIES_DIR "spiderFace.png",&spiderFace.width,&spiderFace.height,&spiderFace.channels,0);
    if (spiderFace.ppointer == nullptr) {
        return false;
    }
    return true;
}
bool loadGraySpider(){
    graySpider.ppointer=stbi_load(ENTITIES_DIR "graySpider.png",&graySpider.width,&graySpider.height,&graySpider.channels,0);
    if (graySpider.ppointer == nullptr) {
        return false;
    }
    return true;
}
bool loadHulkFace(){
    hulkFace.ppointer=stbi_load(ENTITIES_DIR "hulkFace.png",&hulkFace.width,&hulkFace.height,&hulkFace.channels,0);
    if (hulkFace.ppointer == nullptr) {
        return false;
    }
    return true;
}
bool loadGrayHulk(){
    grayHulk.ppointer=stbi_load(ENTITIES_DIR "grayHulk.png",&grayHulk.width,&grayHulk.height,&grayHulk.channels,0);
    if (grayHulk.ppointer == nullptr) {
        return false;
    }
    return true;
}
bool loadPointReactor(){
    pointReactor.ppointer=stbi_load(ENTITIES_DIR "pointReactor.png",&pointReactor.width,&pointReactor.height,&pointReactor.channels,0);
    if (pointReactor.ppointer == nullptr) {
        return false;
    }
    return true;
}


//buttons and ui
Button mStart    = {390, 390, 500, 100};
Button mExit     = {390, 150, 500, 100};
Button pContinue = {390, 390, 500, 100};
Button pRestart  = {390, 270, 500, 100};
Button pMainMenu = {390, 150, 500, 100};
Button player1 = {407,585,195,130};
Button player2={608,585,195,130};
Button player3={809,585,195,130};

void drawPrices(){
    drawTextCentered("$10",    414.0f, 588.0f, 180.0f, 32.0f, 2.0f, glm::vec4(1, 1, 1, 1));
    drawTextCentered("$20", 615.0f, 588.0f, 180.0f, 32.0f, 2.0f, glm::vec4(1, 1, 1, 1));
    drawTextCentered("$30",   816.0f, 588.0f, 180.0f, 32.0f, 2.0f, glm::vec4(1, 1, 1, 1));

}

void canAfford(int p){
    switch(p){ //color them if u can afford them wl default yb2a gray
        case 1: drawRect(414.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
                drawcapFace(465.5f, 620.0f, 75.0f, 86.2f);
                drawRect(615.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
                drawgraySpider(666.5f, 620.0f, 70.0f, 86.2f);
                drawRect(816.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)); 
                drawgrayHulk(867.5f, 620.0f, 80.0f, 86.2f);
                drawPrices();
                break;
        case 2: drawRect(414.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); 
                drawcapFace(465.5f, 620.0f, 75.0f, 86.2f);
                drawRect(615.0f, 588.0f, 180.0f, 125.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                drawspiderFace(666.5f, 620.0f, 70.0f, 86.2f);
                drawRect(816.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)); 
                drawgrayHulk(867.5f, 620.0f, 80.0f, 86.2f);
                drawPrices();
                break;
        case 3: drawRect(414.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); 
                drawcapFace(465.5f, 620.0f, 75.0f, 86.2f);
                drawRect(615.0f, 588.0f, 180.0f, 125.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                drawspiderFace(666.5f, 620.0f, 70.0f, 86.2f);
                drawRect(816.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); 
                drawhulkFace(867.5f, 620.0f, 80.0f, 86.2f);
                drawPrices();
                break;
        default:drawRect(414.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)); 
                drawgrayCap(465.5f, 620.0f, 75.0f, 86.2f);
                drawRect(615.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
                drawgraySpider(666.5f, 620.0f, 70.0f, 86.2f);
                drawRect(816.0f, 588.0f, 180.0f, 125.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)); 
                drawgrayHulk(867.5f, 620.0f, 80.0f, 86.2f);
                drawPrices();
        break;
    }

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

glm::vec4 laneColor(int lane) { //CHANGE COLOR OF HOVRED AND SELECTED LANES
    if (lane == hoverLane || selectedLanes[lane]){
        return glm::vec4(0.700f, 0.700f, 0.700f, 1.0f);}

    return glm::vec4(0.50f, 0.50f, 0.50f, 1.0f);
}


void drawGameScreen(){

        drawRect(0.0f, 0.0f, 1280.0f, 720.0f, glm::vec4(0.239f, 0.239f, 0.239f, 1.0f)); //background
        drawRect(0.0f, 40.0f, 1280.0f, 120.0f, laneColor(1));//lane 1
        drawRect(0.0f, 160.0f, 1280.0f, 15.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f));//lane 1 divider
        drawRect(0.0f, 175.0f, 1280.0f, 120.0f, laneColor(2));//lane 2
        drawRect(0.0f, 295.0f, 1280.0f, 15.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f));//lane 2 divider
        drawRect(0.0f, 310.0f, 1280.0f, 120.0f, laneColor(3));//lane 3
        drawRect(0.0f, 430.0f, 1280.0f, 15.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f));//lane 3 divider
        drawRect(0.0f, 40.0f, 200.0f, 405.0f, glm::vec4(0.102f, 0.137f, 0.494f, 1.0f)); // outer base
        drawRect(5.0f, 45.0f, 190.0f, 395.0f, glm::vec4(0.247f, 0.318f, 0.710f, 1.0f)); // inner base
        drawInfinityGuantlet(50,192,80,110);
        drawRect(0.0f, 445.0f, 1280.0f, 155.0f, glm::vec4(0.239f, 0.239f, 0.239f, 1.0f));//enviroment space
        //player shop will include players and coin count
        //each slot will take 200px since the full thing is 800
        drawRect(200.0f, 580.0f, 810.0f, 140.0f, glm::vec4(0.149f, 0.196f, 0.220f, 1.0f)); // shop border
        drawRect(206.0f, 585.0f, 195.0f, 130.0f, glm::vec4(0.376f, 0.490f, 0.545f, 1.0f)); // player shop
        drawpointReactor(268.5f, 625.0f, 70.0f, 70.0f);
        drawText("Points: $", 215, 608, 2.0f, glm::vec4(1, 1, 1, 1));
        drawRect(407.0f, 585.0f, 195.0f, 130.0f, glm::vec4(0.376f, 0.490f, 0.545f, 1.0f)); 
        drawRect(608.0f, 585.0f, 195.0f, 130.0f, glm::vec4(0.376f, 0.490f, 0.545f, 1.0f)); 
        drawRect(809.0f, 585.0f, 195.0f, 130.0f, glm::vec4(0.376f, 0.490f, 0.545f, 1.0f)); 
        drawplayer();
}