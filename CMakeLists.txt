cmake_minimum_required(VERSION 3.14)
project(OpenGLStarter C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The bundled Template/lib/glfw3.lib is an MSVC build and cannot be linked by
# MinGW, so build GLFW from source instead.
include(FetchContent)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_executable(OpenGLStarter
    Template/main.cpp
    Template/src/glad.c
)

target_include_directories(OpenGLStarter PRIVATE Template/include)
target_link_libraries(OpenGLStarter PRIVATE glfw OpenGL::GL)
