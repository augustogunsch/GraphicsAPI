#pragma once

#include <GLM/glm.hpp>
#include <program.hpp>
#include <list>
#include <iterator>

class light {
private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    std::list <program*> myPrograms;
    void updateProgram(program* program);
public:
    light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    light(glm::vec3 position);
    light() = delete;
    void setPosition(glm::vec3 position);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
    glm::vec3 getPosition() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    void attachProgram(program* program);
    void dettachProgram(program* program);
    void updatePrograms();
};
