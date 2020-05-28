#include <material.hpp>
#include <debug.hpp>

material::material(texture& ambient, texture& diffuse, texture& specular, texture& emission, 
const float& shininess, const float& emissionStrength) 
    : ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), 
    shininess(shininess*128), emissionStrength(emissionStrength)
{}

material::material(const char* ambientPath, const char* diffusePath, const char* specularPath, 
const char* emissionPath, const float& shininess, const float& emissionStrength) 
    : ambient(ambientPath), diffuse(diffusePath), specular(specularPath), emission(emissionPath),
    shininess(shininess*128), emissionStrength(emissionStrength)
{}

void material::setAmbient(texture& ambient) {
    material::ambient = ambient;
    updatePrograms();
}

void material::setDiffuse(texture& diffuse) {
    material::diffuse = diffuse;
    updatePrograms();
}

void material::setSpecular(texture& specular) {
    material::specular = specular;
    updatePrograms();
}

void material::setEmission(texture& emission) {
    material::emission = emission;
    updatePrograms();
}

void material::setShininess(float& shininess) {
    material::shininess = 128*shininess;
    updatePrograms();
}

void material::setEmissionStrength(float& emissionStrength) {
    material::emissionStrength = emissionStrength;
    updatePrograms();
}

texture material::getAmbient() const {
    return ambient;
}

texture material::getDiffuse() const {
    return diffuse;
}

texture material::getSpecular() const {
    return specular;
}

texture material::getEmission() const {
    return emission;
}

float material::getShininess() const {
    return material::shininess;
}

float material::getEmissionStrength() const {
    return material::emissionStrength;
}

void material::dettachProgram(const program& prog) {
    std::vector<program*>::iterator it;
    for(it = myPrograms.begin(); it != myPrograms.end(); ++it) {
        if(*it == &prog)
        {
            myPrograms.erase(it);
            break;
        }
    }
}

void material::attachProgram(program& program) {
    updateProgram(&program);
    myPrograms.push_back(&program);
}

void material::updatePrograms() {
    std::vector<program*>::iterator it;
    for(it = myPrograms.begin(); it != myPrograms.end(); ++it) {
        updateProgram(*it);
    }
}

void material::updateProgram(program* program) {    
    program->use();
    debug::queryErrors("After program's material program used:");
    
    // Setting sampler units
    program->setInt("material.ambient", 0);
    program->setInt("material.diffuse", 1);
    program->setInt("material.specular", 2);
    program->setInt("material.emission", 3);
    debug::queryErrors("After program's material units updated:");
    
    // Using textures
    ambient.use(GL_TEXTURE0);
    diffuse.use(GL_TEXTURE1);
    specular.use(GL_TEXTURE2);
    emission.use(GL_TEXTURE3);
    debug::queryErrors("After program's material maps updated:");
    
    // Setting properties
    program->setFloat("material.shininess", getShininess());
    program->setFloat("material.emissionStrength", getEmissionStrength());
    debug::queryErrors("After program's material floats updated:");
}