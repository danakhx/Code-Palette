#include "Game.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "UI.h"
#include "stb_image.h"
#ifndef ENTITIES_DIR
#define ENTITIES_DIR "Template/src/Entities/"
#endif

std::vector<enemyTest> enemies;
std::vector<player> players;
std::vector<arcReactor> droppedPoints;
std::vector<projectile> projectiles;
int wave = 1;
int hoverLane = -1;
int selectedLane= -1;
int enemyCount=0;
float spawnTimer = 4.0f;
int points=30;

GameState gameState = GameState::MAIN_MENU;
extern GLFWwindow* gWindow;


void restartGame(){
    wave=1;
    enemyCount=0;
    spawnTimer=4.0f;
    enemies.clear();
    players.clear();
    droppedPoints.clear();
    points=30;
    selectedLane=-1;
    projectiles.clear();
}
void updateShop(int cpoints){
    if(cpoints>=30){
        canAfford(3);

    }
    else if(cpoints>=20){
        canAfford(2);
    }
    else if(cpoints>=10){
        canAfford(1);
    }
    else canAfford(0);

}


void renderGame() {
    switch (gameState) {
        case GameState::MAIN_MENU: drawMainMenu();   break;
        case GameState::PLAYING:
        drawGameScreen();
        updateShop(points);

        //testing area
            //drawProjectile(500,500,glm::vec4(1.0f,1.0f,1.0f,1.0f));

        //end testing area

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
        for(const player& p : players){
            if(p.type==1){
                drawRect(p.x,(laneCenter(p.lane)-p.h/2), p.w, p.h, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
            }
            else if(p.type==2){
                drawRect(p.x, (laneCenter(p.lane)-p.h/2), p.w, p.h, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            }
            else{
                drawRect(p.x, (laneCenter(p.lane)-p.h/2), p.w, p.h, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            }
        }
        for(const projectile& proj: projectiles){
            if(proj.side==0){
                drawProjectile(proj.x,laneCenter(proj.lane)+proj.y,glm::vec4(0.0f,1.0f,0.0f,1.0f));
            }
            else{
                drawProjectile(proj.x,laneCenter(proj.lane)+proj.y,glm::vec4(1.0f,0.0f,0.0f,1.0f));
            }

        }
        break;
        case GameState::PAUSED:
        drawGameScreen();
        drawRect(0,0,1280,720, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f));
        drawPauseScreen(); break; 
        default: break;
    }
}
// keyboard presses
void onKey(int key) {
            if (key == GLFW_KEY_ESCAPE) {
            if (gameState == GameState::PLAYING)     gameState = GameState::PAUSED;
            else if (gameState == GameState::PAUSED) gameState = GameState::PLAYING;
}

           /* jump selected lanes */ 
           /* duck selected lanes */ 
         
    }

// mouse clicks
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
        int lane= whatLane(mouseX, mouseY);
        if(lane !=-1){
        selectedLane=lane; return;}
        if(selectedLane!=-1){

        if(isMouseOver(player1,mouseX,mouseY) && points>=10){
            //add new player to players array with position at start of SELECTED LANE
            //then create drawing players function to call in update()
            player p={selectedLane, 200.0f, 100,100,100,1,150,150,20}; //type 1==cap
            players.push_back(p);
            points-=10;
            selectedLane=-1;
        }
        else if(isMouseOver(player2, mouseX,mouseY)&& points>=20){
            player p={selectedLane, 200.0f, 100,100,100,2,150,150,20}; //type 2==spidey
            players.push_back(p);
            points-=20;
            selectedLane=-1;
        }
        else if(isMouseOver(player3,mouseX,mouseY)&& points>=30){
            player p={selectedLane, 205.0f, 100,100,0,3,150,150,20}; //type 3==hulk
            players.push_back(p);
            points-=30;
            selectedLane=-1;
        }}
    }
}
int whatLane(float mouseX, float mouseY){
    if(mouseX<200.0f){
        return -1;
    }
    else if(mouseY>=40.0f && mouseY<160.0f) return 1;
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
enemyTest enemy= {lane, 1280.0, 100,100,150,1};
    enemies.push_back(enemy);
}
void spawnMediumEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,150,2};
    enemies.push_back(enemy);
}
void spawnHardEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,150,3};
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
    if(w==1) return 4;
    else if(w==2) return 6;
    else if(w==3) return 12;
    return 0;}


void update(float deltaTime){
    if(gameState == GameState::PLAYING){
        hoverLane = whatLane(mouseX, mouseY);
        
        for(enemyTest& enemy : enemies){//move with time yaany d=v*t 
            //also use & to move actual enemy not just a copy (pointer)
            enemy.x -= enemy.speed * deltaTime;
            if(enemy.type==1){
                enemy.projTimer-=deltaTime;
                if(enemy.projTimer<=0.0f){
                    projectile proj={enemy.lane, enemy.x, 30.0f,1};
                    projectiles.push_back(proj);
                    enemy.projTimer=2.0f; //reset timer 
            }}
            if(enemy.type==2){
                enemy.projTimer-=deltaTime;
                if(enemy.projTimer<=0.0f){
                    projectile proj={enemy.lane, enemy.x, -30.0f,1};
                    projectiles.push_back(proj);
                    enemy.projTimer=2.0f; 
            }}
        }
        for(player& p: players){
            p.x+=p.speed*deltaTime;
            if(p.type==2){
                p.projTimer-=deltaTime;
                if(p.projTimer<=0.0f){
                    projectile proj={p.lane, p.x, 0.0f,0};
                    projectiles.push_back(proj);
                    p.projTimer=2.0f; 
                }
            }
        }
        for(projectile& proj: projectiles){
            if(proj.side==0){
                proj.x+= 200.0f*deltaTime;
            }
            if(proj.side==1){
                proj.x-= 200.0f*deltaTime;
            }

        }
        //removing projs
        for(int i = projectiles.size() - 1; i >= 0; i--){
        if(projectiles[i].x > 1280.0f || projectiles[i].x < 200.0f){   
        projectiles.erase(projectiles.begin() + i);
    }}

        //TEST LOOP WILL BE REMOVED LATER
        for(int i = enemies.size() - 1; i >= 0; i--){
        if(enemies[i].x + enemies[i].w < 0){
        enemies.erase(enemies.begin() + i);
        }
        }//end of test loop

        spawnTimer += deltaTime;
        if(wave ==1 && enemyCount< 4){
            if (spawnTimer >= 4.0f) {
            spawnEasyEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount++;
        }

        }//wave 2 lazem tb2a mix of easy and medium not just medium
        else if (wave ==2 && enemyCount<6){
            if (spawnTimer >= 4.0f) {
            spawnMediumEnemy(randomLane());
            spawnEasyEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount+=2;
        }

        }//wave 3 mix of all
        else if(wave ==3 && enemyCount<12){
            if (spawnTimer >= 4.0f) {
            spawnHardEnemy(randomLane());
            spawnMediumEnemy(randomLane());
            spawnEasyEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount+=3;
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


