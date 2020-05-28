#pragma once

#include <program.hpp>
#include <iostream>

class texture {
protected:
    unsigned int ID;
    unsigned int unit;
public:
    texture(const char* path, GLenum unit);
    texture(const char* path);
    texture() = delete;
    void use();
    void use(GLenum unit);
};