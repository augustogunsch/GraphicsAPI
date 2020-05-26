#pragma once

#include <GLAD/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

class program {
    unsigned int createShader(const char* path, const char* name, GLenum type);
public:
    unsigned int ID;
    program(const char* vertexPath, const char* fragmentPath);
    void use();
    void setFloat(const char* name, float value) const;
    void setInt(const char* name, int value) const;
    void setMat4(const char* name, glm::mat4 value) const;
    void setVec3(const char* name, glm::vec3 value) const;
};