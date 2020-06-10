#pragma once

#include <GLM/glm.hpp>
#include <program.hpp>
#include <texture.hpp>
#include <vector>
#include <iterator>

class material {
private:
    texture ambient;
    texture diffuse;
    texture specular;
    texture emission;
    float shininess;
    float emissionStrength;
    std::vector <program*> myPrograms;
    void updateProgram(program* program);
public:
    material(texture& ambient, texture& diffuse, texture& specular, texture& emission, 
    const float& shininess, const float& emissionStrength);
    material(const char* ambientPath, const char* diffusePath, const char* specularPath, const char* emissionPath,
    const float& shininess, const float& emissionStrength);
    material() = delete;
    void setAmbient(texture& ambient);
    void setDiffuse(texture& diffuse);
    void setSpecular(texture& specular);
    void setEmission(texture& emission);
    void setShininess(float& shininess);
    void setEmissionStrength(float& emissionStrength);
    texture getAmbient() const;
    texture getDiffuse() const;
    texture getSpecular() const;
    texture getEmission() const;
    float getEmissionStrength() const;
    float getShininess() const;
    void attachProgram(program& program);
    void dettachProgram(const program& program);
    void updatePrograms();
};
