#include "Game.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "UI.h"
#include "stb_image.h"
#include "sound.h"
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
int enemyCount = 0;
float spawnTimer = 4.0f;
int points=30;
bool placedFirstPlayer = false;
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
const float minShrinkScale = 0.5f;
const float basex= 200.0f; // x position where enemies reach the base

GameState gameState = GameState::MAIN_MENU;
extern GLFWwindow *gWindow;

static double doomSceneStart = -1.0;
static bool doomTalkPlayed = false;
static bool capStopPlayed = false;
static bool capAssemblePlayed = false;
static bool doomVoicePlayed = false;
static bool doomCelebPlayed = false;
static const double DOOM_FPS = 4.0; // frames per second
static const int DOOM_FRAMES = 8;
const double DOOM_RISE_DURATION = 0.5;
const int MAG_FRAMES = 8;
const int MAG_FPS = 4;
const double DOOM_SPEECH_DURATION = 2.5;
const double MAG_SPEECH_DURATION = 2.0;
const double TEMPLE_DURATION = 8.0;
// call this once when the scene begins
void startDoomScene()
{
    doomSceneStart = glfwGetTime();
    doomVoicePlayed = false;
    doomCelebPlayed = false;
     doomTalkPlayed = false;
     capStopPlayed = false;
     capAssemblePlayed = false;
}

// true once all 8 frames have played
bool doomSceneDone()
{
    if (doomSceneStart < 0.0)
        return false;

    double seatedDuration =
        (double)(DOOM_FRAMES + 3) / DOOM_FPS;

    double magnetoDuration =
        (double)MAG_FRAMES / MAG_FPS;

    double totalDuration =
        seatedDuration + DOOM_RISE_DURATION + DOOM_SPEECH_DURATION + magnetoDuration + MAG_SPEECH_DURATION + TEMPLE_DURATION;
    ;

    return (glfwGetTime() - doomSceneStart) >= totalDuration;
}

int doomSceneFrame()
{
    if (doomSceneStart < 0.0)
        return 0;
    int f = (int)((glfwGetTime() - doomSceneStart) * DOOM_FPS);
    return f >= DOOM_FRAMES ? DOOM_FRAMES - 1 : f; // hold on the last frame
}

int doomSceneSecondFrame()
{
    if (doomSceneStart < 0.0)
        return 0;

    double secondSheetStart =
        (double)DOOM_FRAMES / DOOM_FPS;

    double elapsed =
        glfwGetTime() - doomSceneStart - secondSheetStart;

    if (elapsed < 0.0)
        return 0;

    int f = (int)(elapsed * DOOM_FPS);

    return f >= 3 ? 2 : f;
}

int magnetoSceneFrame()
{
    if (doomSceneStart < 0.0)
        return 0;

    // Duration of Doom's two seated sprite sheets
    double seatedDuration =
        (double)(DOOM_FRAMES + 3) / DOOM_FPS;

    // When Doom finishes standing and finishes speaking
    double magnetoStart =
        seatedDuration +
        DOOM_RISE_DURATION +
        DOOM_SPEECH_DURATION;

    // Time elapsed since Magneto started his animation
    double elapsed =
        glfwGetTime() - doomSceneStart - magnetoStart;

    if (elapsed < 0.0)
        return 0;

    // Calculate Magneto's current frame
    int frame = (int)(elapsed * MAG_FPS);

    // Hold on the last frame after the animation ends
    return frame >= MAG_FRAMES ? MAG_FRAMES - 1 : frame;
}
void restartGame()
{
    wave = 1;
    enemyCount = 0;
    spawnTimer = 4.0f;
    enemies.clear();
    players.clear();
    impacts.clear();
    hoverLane=-1;
    droppedPoints.clear();
    points=30;
    placedFirstPlayer = false;
    selectedLanes = {false, false, false, false};
    projectiles.clear();
}
void updateShop(int cpoints){ //rendering shop and grayscale
     int count = 0;
        for (int i = 1; i < 4; i++) {
            if (selectedLanes[i]) {
                count++;
            }}
        if(!placedFirstPlayer){
          if(cpoints>=10 && cpoints>=10*count) canAfford(1);
            else canAfford(0);
        return;
    }        
    if(cpoints>=30 && cpoints>=30*count){
        canAfford(3);
    }
    else if (cpoints >= 20 && cpoints >= 20 * count)
    {
        canAfford(2);
    }
    else if (cpoints >= 10 && cpoints >= 10 * count)
    {
        canAfford(1);
    }
    else
        canAfford(0);
}

float slideInFromRight(double time, double delay, float finalX)
{
    float progress = (float)((time - delay) / 0.65);

    if (progress < 0.0f)
        progress = 0.0f;
    if (progress > 1.0f)
        progress = 1.0f;

    return 1280.0f - (1280.0f - finalX) * progress;
}

float slideDownFromTop(double time, double delay, float finalY)
{
    float progress = (float)((time - delay) / 0.8);

    if (progress < 0.0f)
        progress = 0.0f;
    if (progress > 1.0f)
        progress = 1.0f;

    return 720.0f - (720.0f - finalY) * progress;
}


static void drawEntities()
{
        
        drawGameScreen();
        updateShop(points);
        drawText(std::to_string(points).c_str(), 315, 608, 2.0f, glm::vec4(1, 1, 1, 1));
        for (const enemyTest &enemy : enemies)
        {
            float enemyY = laneCenter(enemy.lane) - enemy.h / 2.0f;
            float drawW = enemy.w * HPscale(enemy.hp, enemy.maxhp);
            float drawH = enemy.h * HPscale(enemy.hp, enemy.maxhp);
            float drawX = enemy.x + (enemy.w - drawW) / 2.0f; 
            float drawY = enemyY;
            if (enemy.type == 1)
            {
                drawdoom(drawX, drawY, drawW, drawH);
            }
            else if (enemy.type == 2)
            {
                drawmagneto(drawX, drawY, drawW, drawH);
            }
            else
            {
                drawthanos(drawX, drawY, drawW, drawH);
            }

            float top = laneCenter(enemy.lane) - enemy.h / 2 + enemy.h;
            float w = enemy.w;
            float h = 6.0f;
            float y = top + 2.0f;

            float frac = (float)enemy.hp / enemy.maxhp;
            if (frac < 0.0f)
                frac = 0.0f;

            drawRect(enemy.x, y, w, h, glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));
            drawRect(enemy.x, y, w * frac, h, glm::vec4(0.9f, 0.0f, 0.0f, 1.0f));
        }

        for (const player &p : players)
        {
            float playerY = laneCenter(p.lane) - p.h / 2.0f;
            float drawW = p.w * HPscale(p.hp, p.maxhp);
            float drawH = p.h * HPscale(p.hp, p.maxhp);
            float drawX = p.x + (p.w - drawW) / 2.0f;
            float drawY = playerY;
            float duckH= drawH*0.6f;
            if (p.type == 1)
            {
                if (p.fighting)
                {
                    drawCaptainAmericaFight(drawX, drawY, drawW, drawH, p.fightFrame);
                }

                else if (p.action == PlayerAction::JUMPING)
                {
                    drawCjump(drawX, drawY + p.jumpOffset, drawW, drawH);
                }
                else if (p.action == PlayerAction::DUCKING)
                {
                    drawCcrouch(drawX, drawY, drawW, duckH);
                }
                else
                {
                    drawCaptainAmericaRun(drawX, drawY, drawW, drawH);
                }
            }
            else if (p.type == 2)
            {
                if (p.action == PlayerAction::DUCKING)
                {
                    drawSPcrouch(drawX, drawY - 1, drawW, duckH);
                }
                else
                {
                    drawSPstand(drawX - 5.0f, drawY + p.jumpOffset - 25.0f, drawW + 10.0f, drawH + 12.0f);
                }
            }
            else
            {
                drawhulk(drawX, drawY, drawW, drawH);
            }
            float top = laneCenter(p.lane) - p.h / 2 + p.h;
            float w = p.w;
            float h = 6.0f;
            float y = top + 2.0f;

            float frac = (float)p.hp / p.maxhp;
            if (frac < 0.0f)
                frac = 0.0f;

            drawRect(p.x, y, w, h, glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));
            drawRect(p.x, y, w * frac, h, glm::vec4(0.0f, 0.9f, 0.0f, 1.0f));
        }
        for (const projectile &proj : projectiles)
        {
            float projectileY = laneCenter(proj.lane) + proj.y; // leh
            if (proj.side == 0)
            {
                drawweb(proj.x, projectileY, 40.0f, 25.0f);
            }
            else
            {
                drawProjectile(proj.x, projectileY, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            }
        }
        // DRAW IMPACT EFFECTS HERE

        for (const impactEffect &impact : impacts)
        {

            float impactY = laneCenter(impact.lane) + impact.y;

            drawimpact(
                impact.x,
                impactY,
                60.0f,
                60.0f);
        }

        for (const arcReactor &point : droppedPoints)
        {
            drawpointReactor(point.x, laneCenter(point.lane) - 50.0f, 30.0f, 30.0f);
        }
        

}
void renderGame()
{
    // int doomFrame = (int)(glfwGetTime() * 8.0) % 8;

    if (gameState == GameState::CUTSCENE)
    {
        double elapsed = glfwGetTime() - doomSceneStart;

        // Calculate the different scene timings
        double seatedDuration =
            (double)(DOOM_FRAMES + 3) / DOOM_FPS;

        double doomStandStart =
            seatedDuration + DOOM_RISE_DURATION;

        double magnetoStart =
            doomStandStart + DOOM_SPEECH_DURATION;

        double magnetoDuration =
            (double)MAG_FRAMES / MAG_FPS;

        double magnetoEnd =
            magnetoStart + magnetoDuration;

        double templeStart = magnetoEnd + MAG_SPEECH_DURATION;
        if (elapsed >= templeStart)
        {
            drawtemple();
            drawInfinityGuantlet(35, 115, 200, 200);
            double templeElapsed = elapsed - templeStart;

            drawdoom(slideInFromRight(templeElapsed, 0.0, 650), 70, 160, 160);
            drawmagneto(slideInFromRight(templeElapsed, 0.4, 830), 70, 160, 160);
            drawthanos(slideInFromRight(templeElapsed, 0.8, 1010), 70, 160, 160);

            // Doom's speech bubble appears after everyone arrives
            if (templeElapsed >= 1.45 && templeElapsed < 3.5)
            {
                if (!doomTalkPlayed){
                    playSound("get");
                    doomTalkPlayed = true;
                }
                glm::vec4 bubbleOutline(0.05f, 0.05f, 0.07f, 1.0f);
                glm::vec4 bubbleWhite(1.0f, 1.0f, 1.0f, 1.0f);
                glm::vec4 bubbleText(0.05f, 0.05f, 0.07f, 1.0f);

                // Pointer towards Doom
                drawTriangle(710, 270, 50, -35, bubbleOutline);
                drawTriangle(715, 270, 40, -27, bubbleWhite);

                // Speech bubble
                drawRect(500, 270, 480, 110, bubbleOutline);
                drawRect(504, 274, 472, 102, bubbleWhite);

                // Dialogue
                drawTextCentered(
                    "THERE IT IS!",
                    510, 335, 460, 30,
                    1.8f, bubbleText);

                drawTextCentered(
                    "LET'S GO GET THAT GAUNTLET, DOOMIES!!!",
                    510, 295, 460, 30,
                    1.5f, bubbleText);
            }

            // HEROES ENTER FROM ABOVE
            if (templeElapsed >= 3.5)
            {
                float capY = slideDownFromTop(templeElapsed, 3.5, 70);
                float spiderY = slideDownFromTop(templeElapsed, 3.75, 70);
                float hulkY = slideDownFromTop(templeElapsed, 4.0, 70);

                drawCaptainAmericaRun(260, capY, 120, 120);
                drawSPstand(390, spiderY, 120, 120);
                drawhulk(520, hulkY, 120, 120);
            }

            // CAPTAIN AMERICA'S SPEECH
            if (templeElapsed >= 4.85)
            {
                glm::vec4 outline(0.05f, 0.05f, 0.07f, 1.0f);
                glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
                glm::vec4 textColor(0.05f, 0.05f, 0.07f, 1.0f);

                // Speech bubble pointer
                drawTriangle(310, 255, 50, -35, outline);
                drawTriangle(315, 255, 40, -27, white);

                // Speech bubble
                drawRect(220, 255, 420, 105, outline);
                drawRect(224, 259, 412, 97, white);

                // Dialogue
                if (templeElapsed < 6.3)
                { 
                    if (!capStopPlayed){
                        playSound("stop");
                        capStopPlayed = true;
                    }
                    drawTextCentered(
                        "NOT SO FAST, DOOMIES!",
                        235, 290, 390, 35,
                        1.8f, textColor);
                }
                else
                {
                     if (!capAssemblePlayed){
                        playSound("assemble");
                         capAssemblePlayed = true;
                     }
                    drawTextCentered(
                        "AVENGERS, ASSEMBLE!",
                        235, 290, 390, 35,
                        1.8f, textColor);
                }
            }

            return;
        }
        drawback();

        // Speech bubble colours
        glm::vec4 outline(0.05f, 0.05f, 0.07f, 1.0f);
        glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 textColor(0.05f, 0.05f, 0.07f, 1.0f);

        // Before his animation, Magneto holds his helmet
        if (elapsed < magnetoStart)
        {
            drawm1(285, 224.25f, 126, 181);
            drawt1(890, 224.25f, 161.25f, 180);
        }
        else
        {
            // After Doom's speech, Magneto puts on his helmet
            drawm2(285, 224.25f, 126, 181, magnetoSceneFrame());
            drawt2(890, 224.25f, 170, 231.25f);
        }

        // PHASE 1: Doom is seated
        if (elapsed < seatedDuration)
        {
            if (elapsed < (double)DOOM_FRAMES / DOOM_FPS)
            {
                drawDoomFrame(
                    430, 224.25f, 420, 271.5f,
                    doomSceneFrame());
            }
            else
            {
                drawDoom2Frame(
                    430, 226.5f, 420, 267,
                    doomSceneSecondFrame());
            }

            // Thought bubble appears after Doom's first frame
            if (elapsed >= (1.0 / DOOM_FPS))
            {
                drawthought(650, 370, 260, 268);
                drawInfinityGuantlet(730, 495, 90, 90);
            }
        }

        // PHASE 2: Doom rises
        else if (elapsed < doomStandStart)
        {
            drawup(430, 224.25f, 420, 271.5f);
        }

        // PHASE 3: Doom is standing
        else
        {
            drawfinal(430, 224.25f, 420, 271.5f);
        }

        // Appears when Doom finishes standing
        // Disappears when Magneto starts his animation
        if (elapsed >= doomStandStart && elapsed < magnetoStart) {
            if (!doomVoicePlayed) {
                playSound("doomVoice");
                doomVoicePlayed = true;
            }      
            // Pointer
            drawTriangle(615, 555, 50, -35, outline);
            drawTriangle(620, 555, 40, -27, white);

            // Bubble
            drawRect(345, 555, 590, 120, outline);
            drawRect(349, 559, 582, 112, white);

            drawTextCentered(
                "WE NEED TO GET THE INFINITY GAUNTLET",
                360, 610, 560, 35,
                2.0f, textColor);

            drawTextCentered(
                "TO DOOM HUMANITY!",
                360, 575, 560, 35,
                2.0f, textColor);
        }
        else{
            stopSound("doomVoice");
        }

        // Appears after Magneto finishes putting on his helmet

        // MAGNETO AND THANOS SPEECH BUBBLES

        if (elapsed >= magnetoEnd)
        {
            if (!doomCelebPlayed){
                playSound("doomCeleb");
                doomCelebPlayed = true;
            }
            // Speech bubble colours
            glm::vec4 outline(0.05f, 0.05f, 0.07f, 1.0f);
            glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
            glm::vec4 textColor(0.05f, 0.05f, 0.07f, 1.0f);

            // MAGNETO'S SPEECH BUBBLE

            // Pointer
            drawTriangle(324, 520, 48, -32, outline);
            drawTriangle(329, 520, 38, -24, white);

            // Bubble outline and interior
            drawRect(153, 520, 390, 105, outline);
            drawRect(157, 524, 382, 97, white);

            // Dialogue
            drawTextCentered(
                "DOOM HUMANITY!",
                167, 556, 362, 35,
                2.0f, textColor);

            // THANOS'S SPEECH BUBBLE

            // Pointer
            drawTriangle(951, 520, 48, -32, outline);
            drawTriangle(956, 520, 38, -24, white);

            // Bubble outline and interior
            drawRect(780, 520, 390, 105, outline);
            drawRect(784, 524, 382, 97, white);

            // Dialogue
            drawTextCentered(
                "DOOM HUMANITY!",
                794, 556, 362, 35,
                2.0f, textColor);
        }

        return;
    }

    // drawDoomFrame(400, 200, 280, 180, 0);//checkety
    switch (gameState)
    {
    case GameState::MAIN_MENU:
        drawMainMenu();
        break;
    case GameState::PLAYING:
       drawEntities();
        break;
    case GameState::PAUSED:
        drawEntities();
        drawRect(0, 0, 1280, 720, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f));
        drawPauseScreen();
        break;

    case GameState::WON:
        drawGameScreen();
        drawEntities();
        drawRect(0, 0, 1280, 720, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f));
        drawWinscreen();
        break;

    case GameState::LOST:
        drawGameScreen();
        drawEntities();
        drawRect(0, 0, 1280, 720, glm::vec4(0.0f, 0.0f, 0.0f, 0.8f));
        drawLoseScreen();
        break;

    case GameState::SOUND: drawSoundMenu(); break;
    default:
        break;
    }
}
// keyboard presses

void setPlayerAction(PlayerAction action)
{

    for (player &p : players)
    {

        if ((p.type == 1 || p.type == 2) && p.lane >= 1 && p.lane <= 3 && selectedLanes[p.lane])
        {
            p.action = action;
            p.actionTimer = 0.0f;
            p.jumpOffset = 0.0f;
        }
    }
}
void onKey(int key)
{

    if (key == GLFW_KEY_ESCAPE)
    {
        if (gameState == GameState::PLAYING)
            gameState = GameState::PAUSED;
        else if (gameState == GameState::PAUSED)
            gameState = GameState::PLAYING;

        return;
    }

    if (gameState != GameState::PLAYING)
        return;

    if (key == GLFW_KEY_W || key == GLFW_KEY_UP)
    {
        setPlayerAction(PlayerAction::JUMPING);
    }

    else if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
    {
        setPlayerAction(PlayerAction::DUCKING);
    }
}

// mouse clicks
void onClick(float mouseX, float mouseY)
{
    if (gameState == GameState::MAIN_MENU)
    {
        if (isMouseOver(mStart, mouseX, mouseY))
        {    stopSound("startMusic");
            if (isMouseOver(mExit, mouseX, mouseY))
            {
                glfwSetWindowShouldClose(gWindow, true);
                return;
            }
            gameState = GameState::CUTSCENE;
            startDoomScene();
            return;
        }
        // CUTSCENE HENAAAAA
        // enemies.clear();
        // gameState = GameState::PLAYING;

        // return;
        else if (isMouseOver(mExit, mouseX, mouseY))
        {
            glfwSetWindowShouldClose(gWindow, true);
            return;
        }
        else if (isMouseOver(mSound, mouseX, mouseY))
        {
            gameState = GameState::SOUND;
            return;
        }
    }

    else if (gameState == GameState::PAUSED)
    {
        if (isMouseOver(pContinue, mouseX, mouseY))
        {
            gameState = GameState::PLAYING;
            return;
        }
        else if (isMouseOver(pRestart, mouseX, mouseY))
        {   stopSound("gameSong");
            // restart the game (restart function not done yet)
            restartGame();
            gameState = GameState::PLAYING;
            return;
        }
        else if (isMouseOver(pMainMenu, mouseX, mouseY))
        {
            // restart the game (restart function not done yet)
            restartGame();
            gameState = GameState::MAIN_MENU;
            return;
        }
    }

    else if (gameState == GameState::WON || gameState== GameState::LOST)
    {
         if (isMouseOver(pRestart, mouseX, mouseY))
        {
            // restart the game (restart function not done yet)
            restartGame();
            stopSound("gameSong");
            gameState = GameState::PLAYING;
            return;
        }
        else if (isMouseOver(pMainMenu, mouseX, mouseY))
        {
            // restart the game (restart function not done yet)
            restartGame();
            stopSound("gameSong");
            gameState = GameState::MAIN_MENU;
            return;
        }
    }
    

    else if (gameState == GameState::PLAYING)
    {

        int lane = whatLane(mouseX, mouseY);
        if (lane != -1)
        {
            selectedLanes[lane] = !selectedLanes[lane];
            return;
        }
        if (selectedLanes[1] || selectedLanes[2] || selectedLanes[3])
        {
            int Counter = 0;
            for (int i = 1; i < 4; i++)
            {
                if (selectedLanes[i])
                {
                    Counter++;
                }
            }
            int characterType = 0;
            int characterPrice = 0;
            if (isMouseOver(player1, mouseX, mouseY))
            {
                characterType = 1;
                characterPrice = 10;
            }
        else if ( isMouseOver(player2, mouseX, mouseY)) {
            characterType = 2;
            characterPrice = 20;
        }
        else if (isMouseOver(player3, mouseX, mouseY)) {
            characterType = 3;
            characterPrice = 30;
        }
        if (characterType != 0) {
            if (!placedFirstPlayer && characterType != 1) return;   // first must be player 1
            int total = Counter * characterPrice;
            if (points >= total) {
                for (int i = 1; i < 4; i++) {
                    if (selectedLanes[i]) {
                        
                        if (characterType == 1) {
                            player p = {i, 200.0f, 100, 100, 100, 1, 5,5, 0.0f, 1};
                            players.push_back(p);
                            playSound("capS");
                        }
                        else if (characterType == 2) {
                            player p = {i, 200.0f, 100, 100, 100, 2, 5, 5, 0.0f, 1};
                            players.push_back(p);
                            playSound("spiderS");
                        }
                        else if (characterType == 3) {
                            player p = {i, 205.0f, 100, 100, 0, 3, 7, 7, 0.0f, 1};
                            players.push_back(p);
                            playSound("hulkS");
                        }
                    }
                    
                }
                points -= total;
                placedFirstPlayer = true;

                selectedLanes = {false, false, false, false};
            }}}
}
else if (gameState == GameState::SOUND){
    if (isMouseOver(volInc, mouseX, mouseY))
    {
        increaseVol();
        return;
    }
    else if (isMouseOver(volDec, mouseX, mouseY))
    {
        decreaseVol();
        return;
    }
    else if (isMouseOver(muteB, mouseX, mouseY))
    {
        toggleMute();
        return;
    }
    else if (isMouseOver(returnSound, mouseX, mouseY))
    {
        gameState = GameState::MAIN_MENU;
        return;
    }
}
}

int whatLane(float mouseX, float mouseY)
{
    if (mouseX < 200.0f)
    {
        return -1;
    }
    else if (mouseY >= 40.0f && mouseY < 160.0f)
        return 1;
    else if (mouseY >= 175.0f && mouseY < 295.0f)
        return 2;
    else if (mouseY >= 310.0f && mouseY < 430.0f)
        return 3;
    return -1;
}

float laneCenter(int lane)
{
    if (lane == 1)
    {
        return 100.0f;
    }
    else if (lane == 2)
    {
        return 235.0f;
    }
    else if (lane == 3)
    {
        return 370.0f;
    }
    else
    {
        return 0.0f; // invalid lane
    }
}

float HPscale(int currentHP, int maxHP)
{
    return (float)(0.5f + (1 - 0.5f) * ((float)currentHP / maxHP));
}

void spawnEnemy(int lane)
{
    enemyTest enemy = {lane, 1280.0, 100, 100, 100};
    enemies.push_back(enemy);
}
void spawnEasyEnemy(int lane)
{
    enemyTest enemy = {lane, 1280.0, 100, 100, 150, 1, 5, 5, 0.0f, 1};
    enemies.push_back(enemy);
}
void spawnMediumEnemy(int lane)
{
    enemyTest enemy = {lane, 1280.0, 100, 100, 150, 2, 5, 5, 0.0f, 1};
    enemies.push_back(enemy);
}
void spawnHardEnemy(int lane)
{
    enemyTest enemy = {lane, 1280.0, 100, 100, 150, 3, 7, 7, 0.0f, 1};
    enemies.push_back(enemy);
}
int randomLane()
{
    static int lastLane = 0;
    int lane;
    do
    {
        lane = rand() % 3 + 1;
    } while (lane == lastLane);
    lastLane = lane;
    return lane;
}
int maxCount(int w)
{
    if (w == 1)
        return 4;
    else if (w == 2)
        return 6;
    else if (w == 3)
        return 12;
    return 0;
}

void update(float deltaTime)
{
    if (gameState == GameState::CUTSCENE && doomSceneDone())
    {
        gameState = GameState::PLAYING;
        return;
    }

    if (gameState == GameState::PLAYING)
    {
        hoverLane = whatLane(mouseX, mouseY);
        for (player &p : players)
            p.move = 1; // set all players movable
        for (int i = players.size() - 1; i >= 0; i--)
        { // players die loop
            if (players[i].hp <= 0){
                players.erase(players.begin() + i);
            playSound("playerD");
            }
        }

        // JUMP AND DUCK ANIMATION UPDATE
        for (player &p : players)
        { ///////ayo

            if (p.action == PlayerAction::JUMPING)
            {

                p.actionTimer += deltaTime;

                // Spider-Man jump: smooth upward and downward movement
                float t = p.actionTimer / jumpDuration;

                if (t <= 1.0f)
                {
                    p.jumpOffset = 4.0f * jumpHeight * t * (1.0f - t);
                }

                // Finish jump
                if (p.actionTimer >= jumpDuration)
                {
                    p.action = PlayerAction::RUNNING;
                    p.actionTimer = 0.0f;
                    p.jumpOffset = 0.0f;
                }
            }

            else if (p.action == PlayerAction::DUCKING)
            {

                p.actionTimer += deltaTime;

                if (p.actionTimer >= duckDuration)
                {
                    p.action = PlayerAction::RUNNING;
                    p.actionTimer = 0.0f;
                    p.jumpOffset = 0.0f;
                }
            }
        }

        for (enemyTest &e : enemies)
            e.move = 1; // set all enemmies movable
        for (int i = enemies.size() - 1; i >= 0; i--)
        { // ENEMIES DIE LOOP FOR POINTS AMD REMOVING ENEMIES
            if (enemies[i].hp <= 0)
            {
                arcReactor ar;
                if (enemies[i].type == 1)
                {
                    ar = {enemies[i].lane, enemies[i].x, 15};
                }
                else if (enemies[i].type == 2)
                {
                    ar = {enemies[i].lane, enemies[i].x, 20};
                }
                else
                {
                    ar = {enemies[i].lane, enemies[i].x, 25};
                }
                droppedPoints.push_back(ar);
                enemies.erase(enemies.begin() + i);
                playSound("enemyD");
            }
        }

        for (player &p : players)
        { // players collect points
            for (int i = droppedPoints.size() - 1; i >= 0; i--)
            {
                if (droppedPoints[i].lane == p.lane && p.x + p.w - 10.0f >= droppedPoints[i].x && p.x <= droppedPoints[i].x + 20.0f)
                {
                    points += droppedPoints[i].value;
                    playSound("coin");
                    droppedPoints.erase(droppedPoints.begin() + i);
                }
            }
        }

        for (player &p : players)
        {
            bool touchingEnemy = false; // collisions loop lazm y2ofo

            for (enemyTest &enemy : enemies)
            {
                if (p.lane == enemy.lane && p.x + p.w >= enemy.x && p.x <= enemy.x + enemy.w)
                {
                    enemy.move = 0;
                    p.move = 0;

                    if (p.type == 1)
                    {
                        p.fighting = true;
                        p.fightTimer += deltaTime;
                        if (p.fightTimer >= capFrameDuration)
                        {
                            p.fightTimer = 0.0f;
                            p.fightFrame++;
                            if (p.fightFrame >= 5)
                            {
                                p.fightFrame = 0;
                                enemy.hp -= 1;
                            }
                        }
                    }
                    if (enemy.type == 3)
                    {
                        enemy.projTimer -= deltaTime;
                        if (enemy.projTimer <= 0.0f)
                        {
                            p.hp -= 2;
                            enemy.projTimer = 3.0f;
                        }
                    }
                    touchingEnemy = true;
                }
            }
            // No enemy touching Cap anymore
            if (!touchingEnemy && p.type == 1)
            {
                p.fighting = false;
                p.fightFrame = 0;
                p.fightTimer = 0.0f;
            }
            if (!touchingEnemy)
            {
                p.move = 1;
            }
        }

        for (int i = projectiles.size() - 1; i >= 0; i--)
        {

            projectile proj = projectiles[i];
            bool projectileHit = false;

            // Spider-Man's web hits an enemy
            for (enemyTest &enemy : enemies)
            {

                if (proj.side == 0 &&
                    proj.lane == enemy.lane &&
                    proj.x >= enemy.x &&
                    proj.x <= enemy.x + enemy.w)
                {

                    enemy.hp -= 1;

                    impactEffect impact = {
                        enemy.lane,
                        enemy.x,
                        proj.y,
                        0.0f};

                    impacts.push_back(impact);

                    projectileHit = true;
                    break;
                }
            }

            // Enemy projectile hits a player
            for (player &p : players)
            {
                bool dodged =
                    (p.action == PlayerAction::DUCKING && proj.y > 0.0f) ||
                    (p.action == PlayerAction::JUMPING && proj.y < 0.0f);

                if (proj.side == 1 &&
                    proj.lane == p.lane &&
                    proj.x >= p.x &&
                    proj.x <= p.x + p.w &&
                    !dodged)
                {

                    p.hp -= 1;
                    projectileHit = true;
                }
            }

            // Remove projectile ONLY once
            if (projectileHit)
            {
                projectiles.erase(projectiles.begin() + i);
            }
        }

        for(enemyTest& back : enemies){ //enemies wait behind each other
            for(const enemyTest& front : enemies){
                if(back.lane==front.lane && back.x > front.x && back.x < front.x + front.w + 10.0f){
                    back.move=0;
                }
            }
        }

        for(enemyTest& enemy : enemies){//move with time yaany d=v*t MOVING ENEMIES LOOP AND SHOOTING
            //also use & to move actual enemy not just a copy (pointer)
             if (enemy.x + enemy.w < 200.0f) {
      gameState = GameState::LOST;
      return;
  }  
            if(enemy.move==1){
            enemy.x -= enemy.speed * deltaTime;}
            if(enemy.type==1){
                enemy.projTimer-=deltaTime;
                if(enemy.projTimer<=0.0f){
                    projectile proj={enemy.lane, enemy.x, 30.0f,1};
                    projectiles.push_back(proj);
                    enemy.projTimer = 4.0f; // reset timer
                }
            }
            if (enemy.type == 2)
            {
                enemy.projTimer -= deltaTime;
                if (enemy.projTimer <= 0.0f)
                {
                    projectile proj = {enemy.lane, enemy.x, -30.0f, 1};
                    projectiles.push_back(proj);
                    enemy.projTimer = 3.5f;
                }
            }
        }
        for (player &p : players)
        { // MOVING PLAYERS AND SPIDERMAN SHOOTS
            if (p.move == 1)
            {
                p.x += p.speed * deltaTime;
            }
            if (p.type == 2)
            {
                p.projTimer -= deltaTime;
                if (p.projTimer <= 0.0f)
                {
                    projectile proj = {p.lane, p.x + p.w, 0.0f, 0};
                    projectiles.push_back(proj);
                    p.projTimer = 1.0f;
                }
            }
        }
        for (projectile &proj : projectiles)
        { // moving projectiles
            if (proj.side == 0)
            {
                proj.x += 200.0f * deltaTime;
            }
            if (proj.side == 1)
            {
                proj.x -= 200.0f * deltaTime;
            }
        }
        for (int i = impacts.size() - 1; i >= 0; i--)
        { // UPDATE IMPACT EFFECTS HERE
            impacts[i].timer += deltaTime;

            if (impacts[i].timer >= 0.25f)
            {
                impacts.erase(impacts.begin() + i);
            }
        }

        // removing projs if they go offscreen

        for (int i = projectiles.size() - 1; i >= 0; i--)
        {

            if (projectiles[i].x > 1280.0f ||
                projectiles[i].x < 200.0f)
            {

                projectiles.erase(projectiles.begin() + i);
            }
        }

        // TEST LOOP WILL BE REMOVED LATER
        for (int i = enemies.size() - 1; i >= 0; i--)
        {
            if (enemies[i].x <= basex)
            {
                gameState = GameState::LOST;
                playSound("loseFirst");
                return;
            }
        } // end of test loop
        // below is wave management kolaha
        spawnTimer += deltaTime;
        if (wave == 1 && enemyCount < 4)
        {
            if (spawnTimer >= 5.0f)
            {
                spawnEasyEnemy(randomLane());
                spawnTimer = 0.0f;
                enemyCount++;
            }

        } // wave 2 lazem tb2a mix of easy and medium not just medium
        else if (wave == 2 && enemyCount < 6)
        {
            if (spawnTimer >= 5.0f)
            {
                spawnMediumEnemy(randomLane());
                spawnEasyEnemy(randomLane());
                spawnTimer = 0.0f;
                enemyCount += 2;
            }

        } // wave 3 mix of all
        else if (wave == 3 && enemyCount < 12)
        {
            if (spawnTimer >= 5.0f)
            {
                int firstLane = randomLane();
                int secondLane = firstLane % 3 + 1;
                int thirdLane = secondLane % 3 + 1;
                spawnHardEnemy(firstLane);
                spawnMediumEnemy(secondLane);
                spawnEasyEnemy(thirdLane);
                spawnTimer = 0.0f;
                enemyCount += 3;
            }
        }
        // update wave / increment wave
        if (enemyCount == maxCount(wave) && enemies.empty())
        {
            if (wave < 3)
            {
                wave++;
                enemyCount = 0;
                spawnTimer = 4.0f;
            }
            else
            {
                gameState = GameState::WON;
                playSound("gameSong");
            }
        }
    }
}

void cleanupGame()
{
}
