#include <camera.hpp>

camera::camera(glm::vec3 pos, glm::vec3 rot, float fov, window* window) {
    setPosition(pos);
    setRotation(rot);
    setFOV(fov);
    
    myWindow = window;
    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);
}

void camera::setPosition(glm::vec3 pos) {
    position = pos;
    changedView = true;
}

void camera::setRotation(glm::vec3 rot) {
    rotation = rot;
    changedView = true;
    changedDirections = true;
}

void camera::setFOV(float fov) {
    FOV = fov;
    changedProjection = true;
}

glm::mat4 camera::getViewMatrix() {
    if(changedView) {
        changedView = false;
        genViewMatrix();
    }
    return viewMatrix;
}

glm::mat4 camera::getProjectionMatrix() {
    if(changedProjection) {
        changedProjection = false;
        genProjectionMatrix();
    }
    return projectionMatrix;
}

void camera::genViewMatrix() {
    glm::mat4 lookAt = glm::lookAt(getPosition(), getPosition() + getFront(), getUp());
    viewMatrix = lookAt;
}

void camera::genProjectionMatrix() {
    glm::mat4 perspective = glm::perspective(getFOV(), (float)myWindow->getWidth()/myWindow->getHeight(), 0.1f, 100.0f);
    projectionMatrix = perspective;
}

void camera::genDirections() {
    float pitch = rotation.x;
    float yaw = rotation.y;
    float roll = rotation.z;
    
    // Relative front
    front = glm::vec3(glm::sin(glm::radians(yaw)), glm::sin(glm::radians(pitch)), glm::cos(glm::radians(pitch))
     * glm::cos(glm::radians(yaw)));
    
    // World up
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Relative right
    right = glm::normalize(glm::cross(front, up));
    
    // Relative up
    relativeUp = glm::normalize(glm::cross(front, right));
}

void camera::checkDirections() {
    if(changedDirections) {
        changedDirections = false;
        genDirections();
    }
}

glm::vec3 camera::getFront() {
    checkDirections();
    return front;
}

glm::vec3 camera::getUp() {
    checkDirections();
    return up;
}

glm::vec3 camera::getRight() {
    checkDirections();
    return right;
}

glm::vec3 camera::getRelativeUp() {
    checkDirections();
    return relativeUp;
}

void camera::moveFrontwards(float amount) {
    setPosition(getPosition() + amount * getFront());
}
void camera::moveRightwards(float amount) {
    setPosition(getPosition() + amount * getRight());
}
void camera::moveUpwards(float amount) {
    setPosition(getPosition() + amount * getUp());
}

glm::vec3 camera::getPosition() {
    return position;
}

glm::vec3 camera::getRotation() {
    return rotation;
}

float camera::getFOV() {
    return FOV;
}