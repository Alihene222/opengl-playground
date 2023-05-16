#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "gfx.hpp"

namespace gfx {

struct VertexBuffer {
    GLuint handle;

    ~VertexBuffer(void);

    void gen_buffers(void);

    void bind(void);

    void unbind(void);

    void buffer(void *data, size_t count, bool dynamic);

    void buffer(size_t count, bool dynamic);

    void buffer_sub(void *data, size_t count);
};

}

#endif
