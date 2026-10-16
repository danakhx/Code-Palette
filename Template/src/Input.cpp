#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"

float mouseX=0, mouseY=0;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        onKey(key);   // defined in Game.cpp
    }
}

void cursorCallback(GLFWwindow* window, double x, double y){
    mouseX= (float)x;
    mouseY= 720.0f -(float)y;

}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        onClick(mouseX, mouseY);
    }
}