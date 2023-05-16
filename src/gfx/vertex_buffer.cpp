#include "vertex_buffer.hpp"

using namespace gfx;

void VertexBuffer::gen_buffers(void) {
    glGenBuffers(1, &handle);
}

void VertexBuffer::bind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VertexBuffer::unbind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::buffer(void *data, size_t count, bool dynamic) {
    glBufferData(GL_ARRAY_BUFFER, count, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VertexBuffer::buffer(size_t count, bool dynamic) {
    glBufferData(GL_ARRAY_BUFFER, count, NULL, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VertexBuffer::buffer_sub(void *data, size_t count) {
    glBufferSubData(GL_ARRAY_BUFFER, 0, count, data);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &this->handle);
}