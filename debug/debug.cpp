#include <debug.hpp>

#include <GLAD/glad.h>

#include <iostream>

void debug::queryErrors(const char* customMsg) {
    GLenum errorCode;
    const char* error;
    while((errorCode = glGetError()) != GL_NO_ERROR) {
        if(customMsg)
            std::cout << customMsg << "\n";
        
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        
        std::cout << "ERROR HAPPENED! NAME: " << error << "; CODE: " << errorCode << "\n";
        throwError();
    }
}

void debug::throwError(const char* customMsg) {
    if(customMsg)
        std::cout << customMsg << "\n";
    
    std::cout << "Press any key to continue." << std::endl;
    std::cin.get();
    exit(-1);
}

void debug::warn(const char* customMsg) {
    std::cout << customMsg << "\n";
}

void debug::log(const char* customMsg) {
    std::cout << customMsg << "\n";
}
