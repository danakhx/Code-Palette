#include "Game.h"
#include "Renderer.h"

GameState gameState = GameState::PLAYING;

void renderGame() {
    switch (gameState) {
        case GameState::MAIN_MENU: drawMainMenu();   break;
        case GameState::PLAYING:   drawGameScreen(); break;
        default: break;
    }
}
void drawGameScreen(){

        drawRect(0.0f, 0.0f, 1280.0f, 720.0f, glm::vec4(0.239f, 0.239f, 0.239f, 1.0f)); //background
        drawRect(0.0f, 40.0f, 1280.0f, 120.0f, glm::vec4(0.620f, 0.620f, 0.620f, 1.0f));//lane 1
        drawRect(0.0f, 160.0f, 1280.0f, 15.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f));//lane 1 divider
        drawRect(0.0f, 175.0f, 1280.0f, 120.0f, glm::vec4(0.620f, 0.620f, 0.620f, 1.0f));//lane 2
        drawRect(0.0f, 295.0f, 1280.0f, 15.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f));//lane 2 divider
        drawRect(0.0f, 310.0f, 1280.0f, 120.0f, glm::vec4(0.620f, 0.620f, 0.620f, 1.0f));//lane 3
        drawRect(0.0f, 430.0f, 1280.0f, 15.0f, glm::vec4(0.933f, 0.933f, 0.933f, 1.0f));//lane 3 divider
        drawRect(0.0f, 40.0f, 200.0f, 405.0f, glm::vec4(0.102f, 0.137f, 0.494f, 1.0f)); // outer base
        drawRect(5.0f, 45.0f, 190.0f, 395.0f, glm::vec4(0.247f, 0.318f, 0.710f, 1.0f)); // inner base
        drawRect(0.0f, 445.0f, 1280.0f, 155.0f, glm::vec4(0.239f, 0.239f, 0.239f, 1.0f));//enviroment space
        drawRect(120.0f, 600.0f, 1040.0f, 120.0f, glm::vec4(0.149f, 0.196f, 0.220f, 1.0f)); // shop border (#263238)
        drawRect(125.0f, 605.0f, 1030.0f, 110.0f, glm::vec4(0.376f, 0.490f, 0.545f, 1.0f)); // player shop

}
void drawMainMenu()   { /* background + buttons */ }
