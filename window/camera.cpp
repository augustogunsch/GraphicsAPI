#include <camera.hpp>

camera::camera(glm::vec3 position, glm::vec3 rotation, float fov, window& window) 
    : position(position), rotation(rotation), FOV(fov), myWindow(window), viewMatrix(1.0f),
    projectionMatrix(1.0f)
{}

void camera::setPosition(glm::vec3 position) {
    camera::position = position;
    changedView = true;
}

void camera::setRotation(glm::vec3 rotation) {
    camera::rotation = rotation;
    changedView = true;
    changedDirections = true;
}

void camera::setFOV(const float& fov) {
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
    viewMatrix = glm::lookAt(getPosition(), getPosition() + getFront(), getUp());
}

void camera::genProjectionMatrix() {
    projectionMatrix = glm::perspective(getFOV(), (float)myWindow.getWidth()/myWindow.getHeight(),
     0.1f, 100.0f);
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
    glm::vec3 front = getFront();
    glm::vec3 position = getPosition();
    setPosition(position + amount * front);
}
void camera::moveRightwards(float amount) {
    setPosition(getPosition() + amount * getRight());
}
void camera::moveUpwards(float amount) {
    setPosition(getPosition() + amount * getUp());
}

glm::vec3 camera::getPosition() const {
    return position;
}

glm::vec3 camera::getRotation() const {
    return rotation;
}

float camera::getFOV() const {
    return FOV;
}