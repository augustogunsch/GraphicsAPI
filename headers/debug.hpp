#pragma once

#include <GLAD/glad.h>
#include <iostream>
#include <exception>

class debug {
public:
    static void queryErrors(const char* customMsg = NULL);
};