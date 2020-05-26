#pragma once

#include <program.hpp>
#include <material.hpp>
#include <camera.hpp>
#include <texture.hpp>
#include <GLM/glm.hpp>

// This class is abstract
class model {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool changedModelMatrix;
    glm::mat4 modelMatrix;
public:
    unsigned int ID;
    camera* myCamera = NULL;
    program* myProgram = NULL;
    model(program *program, camera *camera, glm::vec3 worldPosition, glm::vec3 rot, 
    glm::vec3 scale);
    void genModelMatrix();
    glm::mat4 getModelMatrix();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    void setPosition(glm::vec3 pos);
    void setRotation(glm::vec3 rot);
    void setScale(glm::vec3 scal);
    virtual void render() = 0;
    virtual void use() = 0;
};