#include "Shader.h"
#include <iostream>

// --- Shader sources ---
static const char* vertexShaderSource = R"(
#version 430 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
}
)";

static const char* fragmentShaderSource = R"(
#version 430 core
out vec4 FragColor;

uniform vec4 color;

void main()
{
    FragColor = color;
}
)";

// shader for el texture char

static const char* charvertexShaderSource =R"(
#version 430 core 
layout (location = 0) in vec3 aPos;
layout (location=1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";


static const char* chartextureFragmentShaderSource = R"(
#version 430 core
in vec2 TexCoord;
uniform sampler2D characterTexture;
out vec4 FragColor;
void main()
{
    FragColor = texture(characterTexture,TexCoord);
}
)";



GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compile error:\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint createShaderProgram() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader link error:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint newtextureShaderProgram(){
    GLuint textureVertexShaderSource = compileShader(GL_VERTEX_SHADER, charvertexShaderSource);
    GLuint textureFragmentShaderSource=compileShader(GL_FRAGMENT_SHADER, chartextureFragmentShaderSource);
    GLuint textureshaderProgram = glCreateProgram();
    glAttachShader(textureshaderProgram, textureVertexShaderSource);
    glAttachShader(textureshaderProgram, textureFragmentShaderSource);
    glLinkProgram(textureshaderProgram);
    

    int success=0;
    glGetProgramiv(textureshaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(textureshaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader link error:\n" << infoLog << std::endl;
    }



    glDeleteShader(textureVertexShaderSource);
    glDeleteShader(textureFragmentShaderSource);

    return textureshaderProgram;
}