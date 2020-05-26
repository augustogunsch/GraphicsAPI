#include <texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <STBI/stb_image.h>
#include <debug.hpp>

texture::texture(const char* path, GLenum unit) : texture::texture(path) {
    texture::unit = unit;
}

texture::texture(const char* path) {
    // Setting to flip vertically
    stbi_set_flip_vertically_on_load(true);
    
    // Image loading
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);
    if(!image) {
        std::cout << "TEXTURE LOADING FAILURE:\n" << stbi_failure_reason;
        exit(-1);
    }    
    
    // Texture creation
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    // Wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Scaling parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // Loading texture image into object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    // Generating mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Freeing STBI
    stbi_image_free(image);
    
    // Unbinding texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture::use() {
    use(unit);
}

void texture::use(GLenum unit) {
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}