#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"
#include "CharactersLoad.h"
#include "UI.h"

#include "Renderer.h"
#include <cstdlib>  
#include <ctime>   
#include "sound.h"

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


     if (loadCap()){std::cout << "Captain America sprite loaded!" << std::endl;}
    else{std::cout << "Failed to load Captain America sprite!" << std::endl;}

    if (loadfight()){std::cout << "Captain America fight sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load Captain America fight sprite!" << std::endl;}

     if (loadCcrouch()){std::cout << "Captain America crouch  loaded!" << std::endl;}
    else{std::cout<< "Failed to load Captain America crouch sprite!" << std::endl;}
     
    if (loadCjump()){std::cout << "Captain America j sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load Captain America j sprite!" << std::endl;}

     // villain test
    if (loaddoom()){std::cout << "doom sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load dooom" << std::endl;}

    if (loadmagneto()){std::cout << "magneto sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load magneot sprite" << std::endl;}
    if (loadthanos()){std::cout << "thanos sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load tanos sprite!" << std::endl;}

    if (loadhulk()){std::cout << "hulk sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load hulk sprite" << std::endl;}

    if (loadweb()){std::cout << "web sprite loaded!" << std::endl;}
    else{std::cout<< "Failed to load web sprite" << std::endl;}

    if (loadwebimpact()){std::cout << "imp loaded!" << std::endl;}
    else{std::cout<< "Failed to load imp sprite" << std::endl;}

    //loki test
    if(!loadLoki()) std::cout << "Failed to load Loki image." << std::endl;
    else std::cout << "Loki image loaded!" << std::endl;

    //infinity guantlet
    if(!loadInfinityGuantlet())std::cout << "Failed to load Infinity Gauntlet image." << std::endl;
    else std::cout << "Infinity Gauntlet image loaded!" << std::endl;

    //base
    if(!loadAvengersBase()) std::cout << "Failed to load Avengers Base image." << std::endl;
    else std::cout << "Avengers Base image loaded!" << std::endl;


    //shop tests
    if(!loadCapFace()) std::cout << "Failed to load Captain America face image." << std::endl;
    else std::cout << "Captain America face image loaded!" << std::endl;
    if(!loadGrayCap()) std::cout << "Failed to load Gray Captain America image." << std::endl;
    else std::cout << "Gray Captain America image loaded!" << std::endl;
    if(!loadSpiderFace()) std::cout << "Failed to load Spider-Man face image." << std::endl;
    else std::cout << "Spider-Man face image loaded!" << std::endl;
    if(!loadGraySpider()) std::cout << "Failed to load Gray Spider-Man image." << std::endl;
    else std::cout << "Gray Spider-Man image loaded!" << std::endl;
    if(!loadHulkFace()) std::cout << "Failed to load Hulk face image." << std::endl;
    else std::cout << "Hulk face image loaded!" << std::endl;
    if(!loadGrayHulk()) std::cout << "Failed to load Gray Hulk image." << std::endl;
    else std::cout << "Gray Hulk image loaded!" << std::endl;
    if(!loadPointReactor()) std::cout << "Failed to load Point Reactor image." << std::endl;
    else std::cout << "Point Reactor image loaded!" << std::endl;

    //cutscene part 1
    if(load1()) std::cout << "Doom 1 loaded!\n";
    else std::cout << "Failed to load Doom 1!\n";

    if(load2()) std::cout << "Doom2 loaded!\n";
    else std::cout << "Failed to load Doom 2!\n";

    if(load3()) std::cout << "soldiers loaded!\n";
    else std::cout << "Failed to load soldiers!\n";

    if(loadthought()) std::cout << "thought loaded!\n";
    else std::cout << "Failed to load thought!\n";

     if(loadu()) std::cout << "u loaded!\n";
    else std::cout << "Failed to load u!\n";
     if(loadf()) std::cout << "thought f!\n";
    else std::cout << "Failed to load f!\n";

     if(loadm1()) std::cout << "m1 loaded\n";
    else std::cout << "Failed to load m1\n";
     if(loadm2()) std::cout << "thought m2\n";
    else std::cout << "Failed to load m2\n";

     if(loadt1()) std::cout << "t1 loaded\n";
    else std::cout << "Failed to load t1\n";
     if(loadt2()) std::cout << "thought t2\n";
    else std::cout << "Failed to load t2\n";

    if(loadback()) std::cout << "background\n";
    else std::cout << "Failed to background t2\n";
    if(loadtemple()) std::cout << "temple\n";
    else std::cout << "Failed to load temple\n";




    glViewport(0, 0, 1280, 720);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouse_callback);   
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    
    // --- Set up shader, geometry and projection ---
    initRenderer();
    bool audioReady = initAudio();
    if (audioReady){
        std::cout << "Audio engine initialized!" << std::endl;
        if (loadSound("doomVoice", "Template/src/characters/doom/doom1.wav", true)){
            std::cout << "Doom voice loaded!" << std::endl;
            
        }
        else{
            std::cout << "FAILED to load Doom voice!" << std::endl;
        }
        if (loadSound("startMusic", "Template/src/characters/doom/start.wav", true)){
            std::cout << "Welcome sound loaded!" << std::endl;
            playSound("startMusic");
        }
        else{
            std::cout << "FAILED to load welcome sound!" << std::endl;
        }
        if(loadSound("coin", "Template/src/characters/coin/coin.wav", false)){
             std::cout << "coin" << std::endl;
        }
        else{
            std::cout<<"not coin"<<std::endl;
        }
    }//loading dooms voice
    else{
         std::cout << "FAILED to initialize audio!" << std::endl;
    }
   
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
    if (audioReady){
        shutdownAudio();
    }

    glfwTerminate();
    return 0;
}


