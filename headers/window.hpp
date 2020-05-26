#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <globals.hpp>

class window {
    float previousTime;
    float deltaTime;
    void genDeltaTime();
    int width;
    int height;
    const char* title;
public:
    const char* getTitle();
    int getWidth();
    int getHeight();
    float clearR, clearG, clearB, clearA;
    GLFWwindow* ID;
    window(int width, int height, const char* title);
    void renderFrame();
    void close();
    void setClearColor(float r, float g, float b, float a);
    void clear();
    void use();
    void setCursorPosCallback(GLFWcursorposfun callback);
    float getDeltaTime();
    void resize(int width, int height);
};