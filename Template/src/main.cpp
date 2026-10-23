#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"
#include "CharactersLoad.h"
#include "UI.h"

#include "Renderer.h"
#include <cstdlib>  
#include <ctime>   


GLFWwindow* gWindow = nullptr;

float lastTime= 0.0f;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720,"Code Palette", nullptr, nullptr);
    gWindow=window;
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }
     
      //test :
    if (loadSPSTAND()) {
    std::cout << "Spider-Man image loaded!" << std::endl;}
    else {
    std::cout << "Failed to load Spider-Man image." << std::endl;}
    if (loadSPCROUCH()) {
    std::cout << "Spider-Man crouching image loaded!" << std::endl;} 
    else {std::cout << "Failed to load Spider-Man crouching image." << std::endl;}


    //loki test
    if(!loadLoki()) std::cout << "Failed to load Loki image." << std::endl;
    else std::cout << "Loki image loaded!" << std::endl;

    //infinity guantlet
    if(!loadInfinityGuantlet())std::cout << "Failed to load Infinity Gauntlet image." << std::endl;
    else std::cout << "Infinity Gauntlet image loaded!" << std::endl;

    glViewport(0, 0, 1280, 720);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    
    // --- Set up shader, geometry and projection ---
    initRenderer();
   
    // --- Render loop ---
    lastTime = (float)glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        clearScreen();
        setCrouching(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
        float currentTime= glfwGetTime();
        float deltaTime= currentTime - lastTime;
        lastTime= currentTime;
        update(deltaTime);
        renderGame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // --- Cleanup ---
    cleanupRenderer();
    cleanupGame();

    glfwTerminate();
    return 0;
}
