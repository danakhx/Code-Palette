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

FetchContent_Declare(glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz
)
FetchContent_MakeAvailable(glm)


find_package(OpenGL REQUIRED)

file(GLOB SOURCES CONFIGURE_DEPENDS Template/src/*.cpp)

add_executable(OpenGLStarter
    ${SOURCES}
    Template/src/glad.c
    Template/src/UI3.cpp
)

target_include_directories(OpenGLStarter PRIVATE
    Template/include
    Template/lib
)
target_link_libraries(OpenGLStarter PRIVATE glfw OpenGL::GL glm::glm)

# Absolute path to the character images so they load no matter which
# directory the exe is launched from (e.g. build/).
target_compile_definitions(OpenGLStarter PRIVATE
    CHARACTERS_DIR="${CMAKE_SOURCE_DIR}/Template/src/characters/"
    ENTITIES_DIR="${CMAKE_SOURCE_DIR}/Template/src/Entities/"
)
