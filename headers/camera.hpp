#pragma once
#include <GLM/glm.hpp>
#include <GLM/matrix.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <iostream>
#include <window.hpp>

class camera {
private:
    bool changedView = true;
    bool changedProjection = true;
    bool changedDirections = true;
    void genViewMatrix();
    void genProjectionMatrix();
    void genDirections();
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 position;
    glm::vec3 rotation;
    float FOV;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 relativeUp;
    void checkDirections();
    window myWindow;
public:
    camera(glm::vec3 position, glm::vec3 rotation, float FOV, window& window);
    camera() = delete;
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setFOV(float FOV);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getFront();
    glm::vec3 getUp();
    glm::vec3 getRight(); 
    glm::vec3 getRelativeUp();
    void moveFrontwards(float amount);
    void moveRightwards(float amount);
    void moveUpwards(float amount);
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    float getFOV();
};