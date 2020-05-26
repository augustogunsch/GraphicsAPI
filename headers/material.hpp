#pragma once

#include <glm/glm.hpp>
#include <program.hpp>
#include <texture.hpp>
#include <vector>
#include <iterator>

class material {
    texture* ambient;
    texture* diffuse;
    texture* specular;
    texture* emission;
    float shininess;
    float emissionStrength;
    std::vector <program*> myPrograms;
    void updateProgram(program* program);
    void init(texture* ambient, texture* diffuse, texture* specular, texture* emission, float shininess, 
    float emissionStrength);
public:
    material(texture* ambient, texture* diffuse, texture* specular, texture* emission, float shininess, 
    float emissionStrength);
    material(const char* ambientPath, const char* diffusePath, const char* specularPath, const char* emissionPath,
    float shininess, float emissionStrength);
    material() = delete;
    void setAmbient(texture* ambient);
    void setDiffuse(texture* diffuse);
    void setSpecular(texture* specular);
    void setEmission(texture* emission);
    void setShininess(float shininess);
    void setEmissionStrength(float emissionStrength);
    texture* getAmbient() const;
    texture* getDiffuse() const;
    texture* getSpecular() const;
    texture* getEmission() const;
    float getEmissionStrength() const;
    float getShininess() const;
    void attachProgram(program* program);
    void dettachProgram(program* program);
    void updatePrograms();
};