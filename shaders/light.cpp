#include <light.hpp>

light::light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    light::position = position;
    light::ambient = ambient;
    light::diffuse = diffuse;
    light::specular = specular;
}

light::light(glm::vec3 position) : 
light::light(position, glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.5f)) {}

void light::setPosition(glm::vec3 position) {
    light::position = position;
    updatePrograms();
}

void light::setAmbient(glm::vec3 ambient) {
    light::ambient = ambient;
    updatePrograms();
}

void light::setDiffuse(glm::vec3 diffuse) {
    light::diffuse = diffuse;
    updatePrograms();
}

void light::setSpecular(glm::vec3 specular) {
    light::specular = specular;
    updatePrograms();
}

glm::vec3 light::getPosition() const {
    return light::position;
}

glm::vec3 light::getAmbient() const {
    return light::ambient;
}

glm::vec3 light::getDiffuse() const {
    return light::diffuse;
}

glm::vec3 light::getSpecular() const{
    return light::specular;
}

void light::attachProgram(program* program) {
    myPrograms.push_back(program);
}

void light::dettachProgram(program* program) {
    // ATTENTION: MULTIPLE LIGHTS ARE YET TO BE SUPPORTED
    myPrograms.remove(program);
}

void light::updatePrograms() {
    std::list<program*>::iterator it;
    for(it = myPrograms.begin(); it != myPrograms.end(); ++it) {
        updateProgram(*it);
    }
}

void light::updateProgram(program* program) {
    program->use();
    program->setVec3("light.position", position);
    program->setVec3("light.ambient", ambient);
    program->setVec3("light.diffuse", diffuse);
    program->setVec3("light.specular", specular);
}