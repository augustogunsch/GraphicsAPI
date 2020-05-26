#include <model.hpp>

model::model(program *program, camera *camera, glm::vec3 worldPosition, glm::vec3 rot, 
glm::vec3 scale) {
    myProgram = program;
    myCamera = camera;
    setScale(scale);
    setPosition(worldPosition);
    setRotation(rot);
}

void model::genModelMatrix() {
    glm::mat4 identity = glm::mat4(1.0f);
    modelMatrix = glm::translate(identity, getPosition());
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 model::getModelMatrix() {
    if(changedModelMatrix) {
        changedModelMatrix = false;
        genModelMatrix();
    }
    return modelMatrix;
}

glm::vec3 model::getPosition() {
    return position;
}

glm::vec3 model::getRotation() {
    return rotation;
}

void model::setPosition(glm::vec3 pos) {
    model::position = pos;
    changedModelMatrix = true;
}

void model::setRotation(glm::vec3 rot) {
    model::rotation = rot;
    changedModelMatrix = true;
}

void model::setScale(glm::vec3 scal) {
    model::scale = scal;
    changedModelMatrix = true;
}