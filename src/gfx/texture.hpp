#ifndef GFX_TEXTURE_HPP
#define GFX_TEXTURE_HPP

#include <iostream>

#include "gfx.hpp"
#include "util/util.hpp"

namespace gfx {

struct Texture {
    GLuint handle;
    std::string name;

    Texture(void) = default;

    Texture(std::string name, std::string path);

    ~Texture(void);

    void bind(void);

    void unbind(void);

    void activate(u8 index);


    bool operator==(Texture other) {
        return handle == other.handle && name == other.name;
    }
};

}

#endif