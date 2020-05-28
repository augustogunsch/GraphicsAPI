#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <globals.hpp>

class window {
private:
    float previousTime;
    float deltaTime;
    void genDeltaTime();
    int width;
    int height;
    const char* title;
    float clearR = 1, clearG = 1, clearB = 1, clearA = 1;
    GLFWwindow* ID;
public:
    window() = delete;
    window(int width, int height, const char* title);
    const char* getTitle() const;
    int getWidth() const;
    int getHeight() const;
    void renderFrame();
    void close();
    void setClearColor(float r, float g, float b, float a);
    void clear();
    void use() const ;
    void setCursorPosCallback(GLFWcursorposfun callback);
    float getDeltaTime() const;
    void resize(int width, int height);
    bool getShouldClose() const;
    void setShouldClose(bool shouldClose);
    bool getKeyPress(unsigned int key) const;
};