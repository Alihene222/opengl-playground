#include "vertex_array.hpp"

using namespace gfx;

void VertexArray::gen_buffers(void) {
    glGenVertexArrays(1, &handle);
}

void VertexArray::bind(void) {
    glBindVertexArray(handle);
}

void VertexArray::unbind(void) {
    glBindVertexArray(0);
}

void VertexArray::attrib(u8 index, u8 size, GLenum type, u16 stride, void *ptr) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, ptr);
    glEnableVertexAttribArray(index);
}

VertexArray::~VertexArray(void) {
    glDeleteVertexArrays(1, &this->handle);
}