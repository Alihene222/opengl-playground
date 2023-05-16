#include "window.hpp"

using namespace gfx;

static void error_callback(int err, const char *msg) {
    fprintf(stderr, "GLFW error %i: %s\n", err, msg);
}

Window::Window(std::string name, u16 width, u16 height, bool resizable) {
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()) {
        std::cerr << "GLFW initialization failed\n" << std::endl;
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
    handle = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if(!handle) {
        std::cerr << "Window initialization failed\n" << std::endl;
        std::exit(-1);
    }
}

void Window::init_openGL(void) {
    glfwMakeContextCurrent(handle);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD initialization failed\n" << std::endl;
        std::exit(-1);
    }
    glfwSwapInterval(0);
}

bool Window::is_close_requested(void) {
    return glfwWindowShouldClose(handle);
}

Window::~Window(void) {
    glfwTerminate();
}