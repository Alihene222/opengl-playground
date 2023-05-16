#include <stb/stb_image.h>

#include "texture.hpp"

using namespace gfx;

Texture::Texture(std::string name, std::string path) {
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    int width, height, channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if(data) {
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        std::cerr << "Loading image from path " << path << " failed. Aborting." << std::endl;
        std::exit(-1);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    stbi_image_free(data);

    this->name = name;
}

void Texture::bind(void) {
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::unbind(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::activate(u8 index) {
    glActiveTexture(GL_TEXTURE0 + index);
}

Texture::~Texture(void) {
    glDeleteTextures(1, &this->handle);
}