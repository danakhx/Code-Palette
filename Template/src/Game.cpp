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
std::array<bool, 4> selectedLanes = {false, false, false, false};
int enemyCount=0;
float spawnTimer = 4.0f;
int points=30;


// Captain America movement test
float capX = 100.0f;
float capY = 60.0f;
float capWidth = 90.0f;
float capHeight = 90.0f;

float capSpeed = 150.0f;

float villainX = 850.0f;
float villainY = 60.0f;
float villainWidth = 100.0f;
float villainHeight = 100.0f;

bool capIsFighting = false;

// Captain America fighting animation
int capFightFrame = 0;
float capFightTimer = 0.0f;
const float capFrameDuration = 0.15f;





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
    selectedLanes = {false, false, false, false};
    projectiles.clear();
}
void updateShop(int cpoints){ //rendering shop and grayscale
     int count = 0;
        for (int i = 1; i < 4; i++) {
            if (selectedLanes[i]) {
                count++;
            }}
    if(cpoints>=30 && cpoints>=30*count){
        canAfford(3);
    }
    else if(cpoints>=20 && cpoints>=20*count){
        canAfford(2);
    }
    else if(cpoints>=10 && cpoints>=10*count){
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
        for(const enemyTest& enemy : enemies){
            float enemyY = laneCenter(enemy.lane) - enemy.h / 2.0f;
            if(enemy.type==1){
            drawdoom(enemy.x, enemyY, enemy.w, enemy.h);}
            else if (enemy.type ==2){
            drawmagneto(enemy.x, enemyY, enemy.w, enemy.h); }
            else{
             drawthanos(enemy.x, enemyY, enemy.w, enemy.h);}
            float top = laneCenter(enemy.lane) - enemy.h/2 + enemy.h;    
            float w = enemy.w;                                     
            float h = 6.0f;
            float y = top + 2.0f;

            float frac = (float)enemy.hp / enemy.maxhp;        
            if(frac < 0.0f) frac = 0.0f;

            drawRect(enemy.x, y, w, h, glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));          
            drawRect(enemy.x, y, w * frac, h, glm::vec4(0.9f, 0.0f, 0.0f, 1.0f)); 
    }
        
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
            float top = laneCenter(p.lane) - p.h/2 + p.h;         
            float w = p.w;                                    
            float h = 6.0f;
            float y = top + 2.0f;

            float frac = (float)p.hp / p.maxhp;        
            if(frac < 0.0f) frac = 0.0f;

            drawRect(p.x, y, w, h, glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));        
            drawRect(p.x, y, w * frac, h, glm::vec4(0.0f, 0.9f, 0.0f, 1.0f));
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


void setPlayerAction(PlayerAction action) {

    for (player& p : players) {

        if (selectedLanes[p.lane] && p.type != 3) {
            p.action = action;
            p.actionTimer = 0.0f;
            p.jumpOffset = 0.0f;
        }
    }
}
void onKey(int key) {

    if (key == GLFW_KEY_ESCAPE) {
        if (gameState == GameState::PLAYING)
            gameState = GameState::PAUSED;
        else if (gameState == GameState::PAUSED)
            gameState = GameState::PLAYING;

        return;
    }

    if (gameState != GameState::PLAYING)
        return;

    if (key == GLFW_KEY_W || key == GLFW_KEY_UP) {
        setPlayerAction(PlayerAction::JUMPING);
    }

    else if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) {
        setPlayerAction(PlayerAction::DUCKING);
    }
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
 else if (gameState == GameState::PLAYING) {

    int lane = whatLane(mouseX, mouseY);
    if (lane != -1) {
        selectedLanes[lane] = !selectedLanes[lane];
        return;
    }
    if (selectedLanes[1] || selectedLanes[2] || selectedLanes[3]) {
        int Counter = 0;
        for (int i = 1; i < 4; i++) {
            if (selectedLanes[i]) {
                Counter++;
            }}
        int characterType = 0;
        int characterPrice = 0;
        if (isMouseOver(player1, mouseX, mouseY)) {
            characterType = 1;
            characterPrice = 10;
        }
        else if (isMouseOver(player2, mouseX, mouseY)) {
            characterType = 2;
            characterPrice = 20;
        }
        else if (isMouseOver(player3, mouseX, mouseY)) {
            characterType = 3;
            characterPrice = 30;
        }
        if (characterType != 0) {
            int total = Counter * characterPrice;
            if (points >= total) {
                for (int i = 1; i < 4; i++) {
                    if (selectedLanes[i]) {
                        if (characterType == 1) {
                            player p = {i, 200.0f, 100, 100, 100, 1, 5,5, 0.0f, 1};
                            players.push_back(p);
                        }
                        else if (characterType == 2) {
                            player p = {i, 200.0f, 100, 100, 100, 2, 5, 5, 0.0f, 1};
                            players.push_back(p);
                        }
                        else if (characterType == 3) {
                            player p = {i, 205.0f, 100, 100, 0, 3, 7, 7, 0.0f, 1};
                            players.push_back(p);
                        }
                    }
                }
                points -= total;
                selectedLanes = {false, false, false, false};
            }}}
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
enemyTest enemy= {lane, 1280.0, 100,100,150,1,5,5, 0.0f, 1};
    enemies.push_back(enemy);
}
void spawnMediumEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,150,2, 5, 5, 0.0f, 1};
    enemies.push_back(enemy);
}
void spawnHardEnemy(int lane){
enemyTest enemy= {lane, 1280.0, 100,100,150,3, 7, 7, 0.0f, 1};
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
      for(player& p : players) p.move = 1;
      for(int i = players.size() - 1; i >= 0; i--){
        if(players[i].hp <= 0) players.erase(players.begin() + i);
}

        for(enemyTest& e : enemies) e.move = 1;
        for(int i = enemies.size() - 1; i >= 0; i--){
            if(enemies[i].hp <= 0) enemies.erase(enemies.begin() + i);
}

        for(player& player:players){
            for(enemyTest& enemy: enemies){
                if(player.lane==enemy.lane && (player.x + player.w)>=enemy.x && player.x<=(enemy.x+enemy.w)){
                    enemy.move=0;
                    player.move=0;

                    if(player.type==1){
                        player.projTimer-=deltaTime;
                        if(player.projTimer<=0.0f){
                            enemy.hp-=1;
                            player.projTimer=1.0f; 
                        }
                    }
                    if(enemy.type==3){
                        enemy.projTimer-=deltaTime;
                        if(enemy.projTimer<=0.0f){
                        player.hp-=2;
                        enemy.projTimer=3.0f;
                    }
                }
            }
        }}
        
        for(int i=projectiles.size()-1; i>=0;i--){
            projectile proj= projectiles[i];
            for(enemyTest& enemy: enemies){
                if(proj.side==0 && proj.lane==enemy.lane && proj.x>=enemy.x && proj.x<=(enemy.x+enemy.w)){
                    enemy.hp-=1;
                    projectiles.erase(projectiles.begin()+i); //Because erase doesn’t take an index number; it takes an iterator, which is like a pointer to an element. begin() is an iterator pointing at element 0, so begin() + i points at element i.Because erase doesn’t take an index number; it takes an iterator, which is like a pointer to an element. begin() is an iterator pointing at element 0, so begin() + i points at element i.
                    break;
                }
            }
            for(player& p: players){
                if(proj.side==1 && proj.lane==p.lane && proj.x>=p.x && proj.x<=(p.x+p.w)){
                    p.hp-=1;
                    projectiles.erase(projectiles.begin()+i);
                    break;
                }
            }
        }

        for(enemyTest& enemy : enemies){//move with time yaany d=v*t 
            //also use & to move actual enemy not just a copy (pointer)
            if(enemy.move==1){
            enemy.x -= enemy.speed * deltaTime;}
            if(enemy.type==1){
                enemy.projTimer-=deltaTime;
                if(enemy.projTimer<=0.0f){
                    projectile proj={enemy.lane, enemy.x, 30.0f,1};
                    projectiles.push_back(proj);
                    enemy.projTimer=4.0f; //reset timer 
            }}
            if(enemy.type==2){
                enemy.projTimer-=deltaTime;
                if(enemy.projTimer<=0.0f){
                    projectile proj={enemy.lane, enemy.x, -30.0f,1};
                    projectiles.push_back(proj);
                    enemy.projTimer=3.5f; 
            }}
        }
        for(player& p: players){
            if(p.move==1){
            p.x+=p.speed*deltaTime;}
            if(p.type==2){
                p.projTimer-=deltaTime;
                if(p.projTimer<=0.0f){
                    projectile proj={p.lane, p.x+p.w, 0.0f,0};
                    projectiles.push_back(proj);
                    p.projTimer=1.0f; 
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
            if (spawnTimer >= 5.0f) {
            spawnEasyEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount++;
        }

        }//wave 2 lazem tb2a mix of easy and medium not just medium
        else if (wave ==2 && enemyCount<6){
            if (spawnTimer >= 5.0f) {
            spawnMediumEnemy(randomLane());
            spawnEasyEnemy(randomLane());
            spawnTimer = 0.0f;
            enemyCount+=2;
        }

        }//wave 3 mix of all
        else if(wave ==3 && enemyCount<12){
            if (spawnTimer >= 5.0f) {
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


