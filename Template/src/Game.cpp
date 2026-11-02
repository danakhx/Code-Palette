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
std::vector<impactEffect> impacts;

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

const float jumpDuration = 0.8f;
const float duckDuration = 0.6f;
const float jumpHeight = 80.0f;



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
        drawText(std::to_string(points).c_str(), 315, 608, 2.0f, glm::vec4(1, 1, 1, 1));
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
             float playerY = laneCenter(p.lane) - p.h / 2.0f;
              // Smaller visual dimensions
             float drawW = p.w * 0.75f;
             float drawH = p.h * 0.75f;
            float drawX = p.x + (p.w - drawW) / 2.0f;   // Keep character centered horizontally
             // Keep character anchored to the bottom of its original position
             float drawY = playerY;
            if(p.type==1){
                
                 if(p.fighting){
                    drawCaptainAmericaFight(drawX,drawY, drawW,drawH,p.fightFrame);
                 }
                
                
                
                else if(p.action == PlayerAction::JUMPING){
                     drawCjump(drawX, drawY + p.jumpOffset, drawW, drawH);
                 }
                else if(p.action == PlayerAction::DUCKING){
                    drawCcrouch(drawX, drawY, drawW, drawH);
                }
                else{
                    drawCaptainAmericaRun(drawX, drawY, drawW, drawH);
                }

            }
            else if(p.type==2){
                if(p.action == PlayerAction::DUCKING){
                     drawSPcrouch(drawX, drawY - 15.0f, drawW, drawH);
                }
                else{
                     drawSPstand(drawX  - 15.0f, drawY + p.jumpOffset - 25.0f, drawW+ 25.0f, drawH  + 30.0f);
                }
            }
            else{
                drawhulk(p.x, playerY, p.w, p.h);
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
            float projectileY = laneCenter(proj.lane) + proj.y;//leh
            if(proj.side==0){
                drawweb(proj.x, projectileY, 40.0f, 25.0f);
            }
            else{
                drawProjectile(proj.x,projectileY, glm::vec4(1.0f,0.0f,0.0f,1.0f));
            }
        }
        // DRAW IMPACT EFFECTS HERE

        for(const impactEffect& impact : impacts){

            float impactY = laneCenter(impact.lane) + impact.y;

            drawimpact(
                impact.x,
                impactY,
                60.0f,
                60.0f
            );
        }

        for(const arcReactor& point: droppedPoints){
            drawpointReactor(point.x,laneCenter(point.lane)-50.0f,30.0f,30.0f);
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

        if ((p.type == 1 || p.type == 2) &&  p.lane >= 1 && p.lane <= 3 && selectedLanes[p.lane]) {
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
      for(player& p : players) p.move = 1; //set all players movable
      for(int i = players.size() - 1; i >= 0; i--){ //players die loop
        if(players[i].hp <= 0) players.erase(players.begin() + i); }

        // JUMP AND DUCK ANIMATION UPDATE
        for(player& p : players){///////ayo

            if(p.action == PlayerAction::JUMPING){

                p.actionTimer += deltaTime;

                // Spider-Man jump: smooth upward and downward movement
                float t = p.actionTimer / jumpDuration;

                if(t <= 1.0f){
                    p.jumpOffset = 4.0f * jumpHeight * t * (1.0f-t);
                }

                // Finish jump
                if(p.actionTimer >= jumpDuration){
                    p.action = PlayerAction::RUNNING;
                    p.actionTimer = 0.0f;
                    p.jumpOffset = 0.0f;
                }
            }

            else if(p.action == PlayerAction::DUCKING){

                p.actionTimer += deltaTime;

                if(p.actionTimer >= duckDuration){
                    p.action = PlayerAction::RUNNING;
                    p.actionTimer = 0.0f;
                    p.jumpOffset = 0.0f;
                }
            }
        }



        for(enemyTest& e : enemies) e.move = 1; //set all enemmies movable
        for(int i = enemies.size() - 1; i >= 0; i--){ //ENEMIES DIE LOOP FOR POINTS AMD REMOVING ENEMIES
            if(enemies[i].hp <= 0){
                arcReactor ar;
                if(enemies[i].type==1){
                ar= {enemies[i].lane, enemies[i].x,15};}
                else if(enemies[i].type==2){
                ar= {enemies[i].lane, enemies[i].x,20};}
                else{
                ar= {enemies[i].lane, enemies[i].x,25};}
                droppedPoints.push_back(ar);
                enemies.erase(enemies.begin() + i);
}}

        for(player& p:players){ //players collect points
            for(int i= droppedPoints.size()-1;i>=0;i--){
                if(droppedPoints[i].lane==p.lane && p.x + p.w -10.0f >= droppedPoints[i].x && p.x <= droppedPoints[i].x + 20.0f){
                    points+=droppedPoints[i].value;
                    droppedPoints.erase(droppedPoints.begin()+i);
                }
            }
        }

        for(player& p : players){
            bool touchingEnemy = false;//collisions loop lazm y2ofo
            for(enemyTest& enemy: enemies){
                if(p.lane==enemy.lane && p.x + p.w >= enemy.x && p.x <= enemy.x + enemy.w){
                    touchingEnemy = true;
                    enemy.move=0;
                    p.move=0;

                    if(p.type==1){
                        p.fighting = true;
                        p.fightTimer += deltaTime;
                        if(p.fightTimer >= capFrameDuration){
                            p.fightTimer = 0.0f;
                            p.fightFrame++;
                            if(p.fightFrame >= 5){
                                  p.fightFrame = 0;
                                    enemy.hp -= 1;

                            }
                            
                            
                        }
                    }
                    if(enemy.type==3){
                        enemy.projTimer-=deltaTime;
                        if(enemy.projTimer<=0.0f){
                        p.hp-=2;
                        enemy.projTimer=3.0f;
                    }
                }
                break;
            }
        }
        // No enemy touching Cap anymore
        if(!touchingEnemy && p.type == 1){
             p.fighting = false;
             p.fightFrame = 0;
             p.fightTimer = 0.0f;
    }
    if(!touchingEnemy){
        p.move = 1;
    }
}      
        
for(int i = projectiles.size() - 1; i >= 0; i--){

    projectile proj = projectiles[i];
    bool projectileHit = false;

    // Spider-Man's web hits an enemy
    for(enemyTest& enemy : enemies){

        if(proj.side == 0 &&
           proj.lane == enemy.lane &&
           proj.x >= enemy.x &&
           proj.x <= enemy.x + enemy.w){

            enemy.hp -= 1;

            impactEffect impact = {
                enemy.lane,
                enemy.x,
                proj.y,
                0.0f
            };

            impacts.push_back(impact);

            projectileHit = true;
            break;
        }
    }

    // Enemy projectile hits a player
    for(player& p : players){

        if(proj.side == 1 &&
           proj.lane == p.lane &&
           proj.x >= p.x &&
           proj.x <= p.x + p.w){

            p.hp -= 1;
            projectileHit = true;
            break;
        }
    }

    // Remove projectile ONLY once
    if(projectileHit){
        projectiles.erase(projectiles.begin() + i);
    }
}


        for(enemyTest& enemy : enemies){//move with time yaany d=v*t MOVING ENEMIES LOOP AND SHOOTING
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
        for(player& p: players){ //MOVING PLAYERS AND SPIDERMAN SHOOTS
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
        for(projectile& proj: projectiles){ //moving projectiles
            if(proj.side==0){
                proj.x+= 200.0f*deltaTime;
            }
            if(proj.side==1){
                proj.x-= 200.0f*deltaTime;
            }

        }
        for(int i = impacts.size() - 1; i >= 0; i--){ // UPDATE IMPACT EFFECTS HERE
            impacts[i].timer += deltaTime;

            if(impacts[i].timer >= 0.25f){
                impacts.erase(impacts.begin() + i);
            }
        }

        //removing projs if they go offscreen
        
        for(int i = projectiles.size() - 1; i >= 0; i--){

            if(projectiles[i].x > 1280.0f ||
            projectiles[i].x < 200.0f){

                projectiles.erase(projectiles.begin() + i);
            }
        }


        //TEST LOOP WILL BE REMOVED LATER
        for(int i = enemies.size() - 1; i >= 0; i--){
        if(enemies[i].x + enemies[i].w < 0){
        enemies.erase(enemies.begin() + i);
        }
        }//end of test loop
        //below is wave management kolaha
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


