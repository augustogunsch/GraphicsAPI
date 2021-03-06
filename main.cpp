#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <cube.hpp>
#include <texture.hpp>
#include <program.hpp>
#include <window.hpp>
#include <debug.hpp>
#include <material.hpp>
#include <light.hpp>

#include <iostream>

#include <GLM/gtx/string_cast.hpp>
static void processInput(window& window, camera& camera);
static void cursorPosCallback(GLFWwindow* window, double x, double y);


window projectWindow = window(800.0f, 600.0f, "Minecraft 2.0");
camera projectCamera = camera(glm::vec3(0.0f, 0.0f, -6.0f), 
glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 
projectWindow);
int main() {
    projectWindow.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    program prog = program("assets/shaders/phong/vertex.glsl", 
    "assets/shaders/phong/fragment.glsl");
    debug::queryErrors("After program creation:");
    
    program progLightSrc = program("assets/shaders/light/vertex.glsl", 
    "assets/shaders/light/fragment.glsl");
    debug::queryErrors("After program creation:");
    
    material myMaterial("assets/textures/diamond_ore/ambient.png", 
    "assets/textures/diamond_ore/diffuse.png",
    "assets/textures/diamond_ore/specular.png", 
    "assets/textures/diamond_ore/emission.png", 0.2f, 0.0f);
    myMaterial.attachProgram(prog);
    
    glm::vec3 lightPosition(-2.0f, 3.0f, 0.0f);
    light myLight(lightPosition);
    myLight.setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    myLight.setDiffuse(glm::vec3(1.0f, 0.5f, 0.1f));
    myLight.setSpecular(glm::vec3(1.0f, 0.5f, 0.1f));
    myLight.attachProgram(&prog);
    myLight.attachProgram(&progLightSrc);
    
    prog.use();
    
    progLightSrc.use();
    debug::queryErrors("After uniforms assignments:");
    
    projectWindow.setCursorPosCallback(cursorPosCallback);
    debug::queryErrors("After cursor callback assignment:");
    
    cube myCube = cube(prog, projectCamera, glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f));
    debug::queryErrors("After cube creation:");
    cube myLightCube = cube(progLightSrc, projectCamera, lightPosition, 
    glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    debug::queryErrors("After light cube creation:");
    
    static const int cubePosSize = 7;
    glm::vec3 cubePos[cubePosSize] = {
        glm::vec3(0.0f, 2.0f, 0.0f),
        glm::vec3(3.0f, 2.0f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-3.0f, 1.0f, 3.0f),
        glm::vec3(-2.0f, -2.0f, 1.0f),
        glm::vec3(3.0f, -2.0f, 1.0f),
        glm::vec3(0.0f, 5.0f, -5.0f)
    };
    
    // RENDER LOOP
    debug::queryErrors("Before render loop:");
    while(!projectWindow.getShouldClose()) {
        projectWindow.clear();
        
        prog.use();
        
        float time = glfwGetTime();
        float cosTime = glm::cos(time);
        float sinTime = glm::sin(time);
        float cosTimeAbs = glm::abs(cosTime);
        float sinTimeAbs = glm::abs(sinTime);
        
        // myMaterial.setEmissionStrength(cosTimeAbs);
        debug::queryErrors("After emission strength assign");
        
        // float radius = 6.0f;
        // lightPosition = glm::vec3(cosTime*radius, 3.0f, sinTime*radius);
        
        myLight.setPosition(lightPosition);
        myLightCube.setPosition(lightPosition);
        
        // lightColor = glm::vec3(cosTimeAbs, sinTimeAbs, 0.0f);
        // progLightSrc.use();
        // progLightSrc.setVec3("lightColor", lightColor);
        // prog.use();
        // prog.setVec3("lightColor", lightColor);
        
        myLightCube.render();
        for(int i = 0; i < cubePosSize; i++) {
            // float rotation = (i+1) * 32 * time;
            float rotation = (i+1) * 32;
            
            myCube.setRotation(glm::vec3(rotation, rotation, rotation));
            myCube.setPosition(cubePos[i]);
            
            myCube.render();
        }
        
        debug::queryErrors("During cube rendering:");
        
        projectWindow.renderFrame();
        debug::queryErrors("During frame rendering:");
        
        processInput(projectWindow, projectCamera);
        debug::queryErrors("During input processing:");
        
        debug::queryErrors("During render loop:");
    }
    
    projectWindow.close();
    return 0;
}

static void processInput(window& window, camera& camera) {
    static float camBaseSpeed = 6.0f;
    static float camSpeed = camBaseSpeed;
    
    if(window.getKeyPress(GLFW_KEY_ESCAPE)) {
        window.setShouldClose(true);
    }
    
    float translation = window.getDeltaTime() * camSpeed;
    if(window.getKeyPress(GLFW_KEY_W)) {
        camera.moveFrontwards(translation);
    }
    if(window.getKeyPress(GLFW_KEY_A)) {
        camera.moveRightwards(-translation);
    }
    if(window.getKeyPress(GLFW_KEY_S)) {
        camera.moveFrontwards(-translation);
    }
    if(window.getKeyPress(GLFW_KEY_D)) {
        camera.moveRightwards(translation);
    }
    if(window.getKeyPress(GLFW_KEY_SPACE)) {
        camera.moveUpwards(translation);
    }
    if(window.getKeyPress(GLFW_KEY_LEFT_SHIFT)) {
        camera.moveUpwards(-translation);
    }
    
    if(window.getKeyPress(GLFW_KEY_LEFT_CONTROL)) {
        camSpeed = 2 * camBaseSpeed;
    }
    else {
        camSpeed = camBaseSpeed;
    }    
}

static double previousX = projectWindow.getWidth()/2;
static double previousY = projectWindow.getHeight()/2;
static void cursorPosCallback(GLFWwindow* window, double x, double y) {
    static float sensibility = 12.0f;
    
    float deltaX = sensibility * (x - previousX);
    float deltaY = sensibility * (y - previousY);
    
    glm::vec3 camRot = projectCamera.getRotation();
    
    float pitch = camRot.x - (deltaY * projectWindow.getDeltaTime());
    float yaw = camRot.y - (deltaX * projectWindow.getDeltaTime());
    
    pitch = glm::clamp(pitch, -89.99f, 89.99f);
    
    projectCamera.setRotation(glm::vec3(pitch, yaw, 0.0f));
    
    previousX = x;
    previousY = y;
}
