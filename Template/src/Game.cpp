#include "Game.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"
#include "UI.h"
#include "stb_image.h"
#ifndef ENTITIES_DIR
#define ENTITIES_DIR "Template/src/Entities/"
#endif
#include <vector>

std::vector<enemyTest> enemies;
std::vector<player> players;
std::vector<arcReactor> points;
int wave = 1;
int hoverLane = -1;
int hoverCard =-1;
int enemyCount=0;
float spawnTimer = 4.0f;

GameState gameState = GameState::MAIN_MENU;
extern GLFWwindow* gWindow;


void restartGame(){
    wave=1;
    enemyCount=0;
    spawnTimer=4.0f;
    enemies.clear();
    players.clear();
    points.clear();
}


void renderGame() {
    switch (gameState) {
        case GameState::MAIN_MENU: drawMainMenu();   break;
        case GameState::PLAYING:
        drawGameScreen();
        for(const enemyTest& enemy : enemies){
            if(enemy.type==1){
            drawRect(enemy.x, (laneCenter(enemy.lane)-enemy.h/2), enemy.w, enemy.h, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        else if (enemy.type ==2){
            drawRect(enemy.x, (laneCenter(enemy.lane)-enemy.h/2), enemy.w, enemy.h, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        
        }
        else{
            drawRect(enemy.x, (laneCenter(enemy.lane)-enemy.h/2), enemy.w, enemy.h, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        
        }}
        break;
        case GameState::PAUSED:
        drawGameScreen();
        drawRect(0,0,1280,720, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f));
        drawPauseScreen(); break; 
        default: break;
    }
}
void onKey(int key) {
            if (key == GLFW_KEY_ESCAPE) {
            if (gameState == GameState::PLAYING)     gameState = GameState::PAUSED;
            else if (gameState == GameState::PAUSED) gameState = GameState::PLAYING;
}

           /* jump selected lanes */ 
           /* duck selected lanes */ 
         
    }

//  LESA HA3MEL EL ONLICK FUNCTION
void onClick(float mouseX, float mouseY){
    if(gameState == GameState::MAIN_MENU){
        if(isMouseOver(mStart, mouseX, mouseY)){
            //CUTSCENE HENAAAAA
            enemies.clear();
            gameState = GameState::PLAYING;
            
             return;
        }
        else if(isMouseOver(mExit, mouseX, mouseY)){
            glfwSetWindowShouldClose(gWindow, true);return;
        }
    }
    else if(gameState == GameState::PAUSED){
        if(isMouseOver(pContinue, mouseX, mouseY)){
            gameState = GameState::PLAYING; return;
        }
        else if(isMouseOver(pRestart, mouseX, mouseY)){
            // restart the game (restart function not done yet)
            restartGame();
            gameState = GameState::PLAYING; return;
        }
        else if(isMouseOver(pMainMenu, mouseX, mouseY)){
            //restart the game (restart function not done yet)
            restartGame();
            gameState = GameState::MAIN_MENU; return;

        }
    }
    else if(gameState == GameState::PLAYING){
        //PLAYING KOL HAGA BA2A 
    }
}
int whatLane(float mouseX, float mouseY){
    if(mouseX<200.0f){
        return -1;
    }
    else if(mouseY>=20.0f && mouseY<160.0f) return 1;
    else if(mouseY>= 175.0f && mouseY< 295.0f)return 2;
    else if(mouseY>=310.0f && mouseY<430.0f)return 3;
    return -1;

}

float laneCenter(int lane){
    if(lane ==1){
        return 100.0f;
    }
    else if(lane ==2){
        return 235.0f;
    }
    else if(lane ==3){
        return 370.0f;
    }
    else{
        return 0.0f; //invalid lane
    }
}


void spawnEnemy(int lane){
    enemyTest enemy= {lane, 1280.0, 100,100,100};
    enemies.push_back(enemy);

}
void spawnEasyEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,50,1};
    enemies.push_back(enemy);
}
void spawnMediumEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,50,2};
    enemies.push_back(enemy);
}
void spawnHardEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,80,3};
    enemies.push_back(enemy);
}
int randomLane() {
    static int lastLane = 0;
    int lane;
    do {
        lane = rand() % 3 + 1;
    } while (lane == lastLane);
    lastLane = lane;
    return lane;
}
int maxCount(int w){
    if(w == 1) return 4;
    if(w == 2) return 7;
    if(w == 3) return 10;
    return 0;
}

void update(float deltaTime){
    if(gameState == GameState::PLAYING){
        hoverLane = whatLane(mouseX, mouseY);
        for(enemyTest& enemy : enemies){//move with time yaany d=v*t 
            //also use & to move actual enemy not just a copy (pointer)
            enemy.x -= enemy.speed * deltaTime;
        }
        //TEXT LOOP WILL BE REMOVED LATER
        for(int i = enemies.size() - 1; i >= 0; i--){
    if(enemies[i].x + enemies[i].w < 0){
        enemies.erase(enemies.begin() + i);
    }
}//end of test loop

        spawnTimer += deltaTime;
        if(wave ==1 && enemyCount< maxCount(1)){
            if (spawnTimer >= 4.0f) {
            spawnEasyEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount++;
        }

        }
        else if (wave ==2 && enemyCount<maxCount(2)){
            if (spawnTimer >= 4.0f) {
            spawnMediumEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount++;
        }

        }
        else if(wave ==3 && enemyCount<maxCount(3)){
            if (spawnTimer >= 4.0f) {
            spawnHardEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount++;
        }
        }
        //update wave / increment wave
        if(enemyCount == maxCount(wave) && enemies.empty()){
            if(wave < 3){
                wave++;
                enemyCount = 0;
                spawnTimer = 4.0f; 
    } else {
        gameState = GameState::WON;
    }
}
    }
}
void cleanupGame(){
    
}


