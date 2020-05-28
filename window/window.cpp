#include <window.hpp>

static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

window::window(int width, int height, const char* title) 
    : width(width), height(height), title(title)
{
    if(!glfwInit()) {
        std::cout << "GLFW INIT FAILURE";
        exit(-1);
    }
    
    previousTime = glfwGetTime();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorGLVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorGLVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLProfile);
    
    ID = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!ID) {
        std::cout << "GLFW WINDOW CREATION FAILURE";
        glfwTerminate();
        exit(-1);
    }
    
    glfwSetFramebufferSizeCallback(ID, framebufferSizeCallback);
    glfwMakeContextCurrent(ID);
    glfwSwapInterval(1);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD INIT FAILURE";
        exit(-1);
    }
    
    glfwSetInputMode(ID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);
}

void window::close() {
    glfwDestroyWindow(ID);
    glfwTerminate();
}

void window::renderFrame() {
    glfwSwapBuffers(ID);
    glfwPollEvents();
    genDeltaTime();
}

void window::use() const {
    glfwMakeContextCurrent(ID);
}

void window::setClearColor(float r, float g, float b, float a) {
    clearR = r;
    clearG = g;
    clearB = b;
    clearA = a;
}

void window::clear() {
    use();
    glClearColor(clearR, clearG, clearB, clearA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void window::setCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(ID, callback);
}

void window::genDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}

float window::getDeltaTime() const {
    return deltaTime;
}

int window::getWidth() const {
    return width;
}

int window::getHeight() const {
    return height;
}

void window::resize(int width, int height) {
    glfwSetWindowSize(ID, width, height);
    window::width = width;
    window::height = height;
}

const char* window::getTitle() const {
    return title;
}

bool window::getShouldClose() const {
    return glfwWindowShouldClose(ID);
}

void window::setShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(ID, shouldClose);
}

bool window::getKeyPress(unsigned int key) const {
    bool pressed = glfwGetKey(ID, key) == GLFW_PRESS;
    return pressed;
}