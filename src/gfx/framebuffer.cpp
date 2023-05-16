#include "framebuffer.hpp"

using namespace gfx;

void Framebuffer::gen_buffers(void) {
    glGenFramebuffers(1, &this->handle);
}

void Framebuffer::bind(void) {
    glBindFramebuffer(GL_FRAMEBUFFER, this->handle);
}

void Framebuffer::unbind(void) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool Framebuffer::is_complete(void) {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::attach_renderbuffer(Renderbuffer renderbuffer, GLenum attachment_type) {
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        attachment_type,
        GL_RENDERBUFFER,
        renderbuffer.handle
    );
    this->renderbuffer = renderbuffer;
}

void Framebuffer::gen_texture(u16 resolution_x, u16 resolution_y) {
    this->texture.gen_buffers();
    this->texture.bind();
    this->texture.fill_data(resolution_x, resolution_y);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    attach_texture(this->texture);
}

void Framebuffer::attach_texture(const FramebufferTexture &texture) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.handle, 0); 
}

Framebuffer::~Framebuffer(void) {
    glDeleteFramebuffers(1, &this->handle);
}

void Renderbuffer::gen_buffers(void) {
    glGenRenderbuffers(1, &this->handle);
}

void Renderbuffer::bind(void) {
    glBindRenderbuffer(GL_RENDERBUFFER, this->handle);
}

void Renderbuffer::unbind(void) {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Renderbuffer::set_storage(GLenum internal_format, u16 resolution_x, u16 resolution_y) {
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        internal_format,
        resolution_x,
        resolution_y
    );
}

Renderbuffer::~Renderbuffer(void) {
    glDeleteRenderbuffers(1, &this->handle);
}

void FramebufferTexture::gen_buffers(void) {
    glGenTextures(1, &this->handle);
}

void FramebufferTexture::bind(void) {
    glBindTexture(GL_TEXTURE_2D, this->handle);
}

void FramebufferTexture::unbind(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FramebufferTexture::fill_data(u16 resolution_x, u16 resolution_y) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution_x, resolution_y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
}

FramebufferTexture::~FramebufferTexture() {
    glDeleteTextures(1, &this->handle);
}

void Framebuffer::bind_default_framebuffer(void) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}