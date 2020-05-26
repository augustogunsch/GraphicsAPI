#include <program.hpp>

program::program(const char* vertexPath, const char* fragmentPath) {
    // Shader creation
    unsigned int vertex = createShader(vertexPath, "VERTEX", GL_VERTEX_SHADER);
    unsigned int fragment = createShader(fragmentPath, "FRAGMENT", GL_FRAGMENT_SHADER);
    
    // If shader creation was unsuccesfull, then leave
    if(vertex == 0 || fragment == 0) {
        exit(-1);
    }
    
    // Program creating and shader attaching
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    // Program linking    
    glLinkProgram(ID);
    unsigned const int bufferSize = 256;
    char infoLog[bufferSize];
    GLint status;
    glGetProgramiv(ID, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        glGetProgramInfoLog(ID, bufferSize, NULL, infoLog);
        std::cout << "SHADER PROGRAM LINK FAILURE:\n" << infoLog;
        exit(-1);
    }
    
    // Shader destruction
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    // Program unusing
    glUseProgram(0);
}

unsigned int program::createShader(const char* path, const char* name, GLenum type) {
    std::fstream stream;
    std::stringstream sStream;
    
    const char* shaderSource;
    
    stream.exceptions(std::ios::failbit | std::ios::badbit);
    try {
        // Source loading
        stream.open(path);
        sStream << stream.rdbuf();
        stream.close();
        std::string shaderSource = sStream.str();
        
        const char* csntCharSource = shaderSource.c_str();
        
        // Shader creation
        unsigned int shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &csntCharSource, NULL);
        glCompileShader(shaderID);
        
        
        // Shader compilation
        GLint status;
        unsigned const int bufferSize = 256;
        char infoLog[bufferSize];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE) {
            glGetShaderInfoLog(shaderID, bufferSize, NULL, infoLog);
            throw std::runtime_error(infoLog);
        }
            
        return shaderID;
    }
    catch(std::ios::failure e) {
        std::cout << name << " LOADING FAILURE:\n" << e.what();
    }
    catch(std::runtime_error e) {
        std::cout << name << " COMPILING FAILURE:\n" << e.what();
    }
    return 0;
}

void program::use() {
    glUseProgram(ID);
}

void program::setFloat(const char* name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void program::setInt(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void program::setMat4(const char* name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void program::setVec3(const char* name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}