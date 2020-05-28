#include <model.hpp>

model::model(program& program, camera& camera, const glm::vec3& worldPosition, 
const glm::vec3& rotation, const glm::vec3& scale) 
    : myProgram(program), myCamera(camera), position(worldPosition), rotation(rotation),
    scale(scale)
{}

void model::genModelMatrix() {
    modelMatrix = glm::translate(glm::mat4(1.0f), getPosition());
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

glm::vec3 model::getPosition() const {
    return position;
}

glm::vec3 model::getRotation() const {
    return rotation;
}

void model::setPosition(const glm::vec3& pos) {
    model::position = pos;
    changedModelMatrix = true;
}

void model::setRotation(const glm::vec3& rot) {
    model::rotation = rot;
    changedModelMatrix = true;
}

void model::setScale(const glm::vec3& scal) {
    model::scale = scal;
    changedModelMatrix = true;
}