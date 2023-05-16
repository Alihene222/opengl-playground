#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include "gfx.hpp"
#include "util/util.hpp"

namespace gfx {

struct Window {
    GLFWwindow *handle;

    Window() = default;

    Window(std::string name, u16 width, u16 height, bool resizable);

    ~Window(void);

    void init_openGL(void);

    bool is_close_requested(void);
};

}

#endif