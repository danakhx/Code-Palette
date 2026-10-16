#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Renderer.h"

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);
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

    glViewport(0, 0, 800, 600);

    // --- Build shader program ---
    GLuint shaderProgram = createShaderProgram();

    // --- Set up geometry ---
    initRenderer();

    // --- Render loop ---
    while (!glfwWindowShouldClose(window)) {
        render(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // --- Cleanup ---
    cleanupRenderer();
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
