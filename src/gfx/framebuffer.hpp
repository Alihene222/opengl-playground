#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "util/util.hpp"
#include "gfx.hpp"

namespace gfx {

struct Renderbuffer {
    GLuint handle;

    ~Renderbuffer(void);

    void gen_buffers(void);

    void bind(void);

    void unbind(void);

    void set_storage(GLenum internal_format, u16 resolution_x, u16 resolution_y);
};

struct FramebufferTexture {
    GLuint handle;

    ~FramebufferTexture(void);

    void gen_buffers(void);

    void bind(void);

    void unbind(void);

    void fill_data(u16 resolution_x, u16 resolution_y);
};

class Framebuffer {
public:
    GLuint handle;
    Renderbuffer renderbuffer;
    FramebufferTexture texture;

    ~Framebuffer(void);

    void gen_buffers(void);

    void bind(void);

    void unbind(void);

    bool is_complete(void);

    void attach_renderbuffer(Renderbuffer renderbuffer, GLenum attachment_type);

    void gen_texture(u16 resolution_x, u16 resolution_y);

    static void bind_default_framebuffer(void);
private:
    void attach_texture(const FramebufferTexture &texture);
};

}

#endif