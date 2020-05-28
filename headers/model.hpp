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
    bool changedModelMatrix = true;
    glm::mat4 modelMatrix;
protected:
    unsigned int ID;
    camera& myCamera;
    program& myProgram;
public:
    model(program& program, camera& camera, const glm::vec3& worldPosition, 
    const glm::vec3& rotation, const glm::vec3& scale);
    model() = delete;
    void genModelMatrix();
    glm::mat4 getModelMatrix();
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scal);
    virtual void render() = 0;
    virtual void use() = 0;
};