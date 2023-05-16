#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "gfx.hpp"
#include "util/util.hpp"

namespace gfx {

struct VertexArray {
    GLuint handle;

    ~VertexArray(void);

    void gen_buffers(void);

    void bind(void);

    void unbind(void);

    void attrib(u8 index, u8 size, GLenum type, u16 stride, void *ptr);

};

}

#endif
