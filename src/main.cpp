#include "gfx/window.hpp"
#include "gfx/vertex_array.hpp"
#include "gfx/vertex_buffer.hpp"
#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "gfx/framebuffer.hpp"

static f32 vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
};

static f32 screen_vertices[] = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
};

static glm::ivec2 win_dimensions = glm::ivec2(1280, 640);
static glm::mat4 projection = glm::perspective(glm::radians(45.0f), (f32) win_dimensions.x / (f32) win_dimensions.y, 0.1f, 100.0f);

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    gfx::Window window("LearnOpenGL", win_dimensions.x, win_dimensions.y, false);
    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    window.init_openGL();

    gfx::Shader shader("res/shaders/core.vert", "res/shaders/core.frag");
    gfx::Shader screen_shader("res/shaders/post.vert", "res/shaders/post.frag");

    gfx::VertexArray vao;
    vao.gen_buffers();
    vao.bind();

    gfx::VertexBuffer vbo;
    vbo.gen_buffers();
    vbo.bind();
    vbo.buffer(vertices, sizeof(vertices), false);

    vao.attrib(0, 3, GL_FLOAT, 6 * sizeof(f32), (void*) 0);
    vao.attrib(1, 2, GL_FLOAT, 6 * sizeof(f32), (void*) (3 * sizeof(f32)));
    vao.attrib(2, 1, GL_FLOAT, 6 * sizeof(f32), (void*) (5 * sizeof(f32)));

    gfx::VertexArray screen_vao;
    screen_vao.gen_buffers();
    screen_vao.bind();

    gfx::VertexBuffer screen_vbo;
    screen_vbo.gen_buffers();
    screen_vbo.bind();
    screen_vbo.buffer(screen_vertices, sizeof(screen_vertices), false);

    screen_vao.attrib(0, 3, GL_FLOAT, 5 * sizeof(f32), (void*) 0);
    screen_vao.attrib(1, 2, GL_FLOAT, 5 * sizeof(f32), (void*) (3 * sizeof(f32)));

    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gfx::Texture texture("holder", "res/textures/texture.png");

    i32 tex_slots[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    gfx::Framebuffer framebuffer;
    framebuffer.gen_buffers();
    framebuffer.bind();
    framebuffer.gen_texture(1280, 640);
    
    gfx::Renderbuffer renderbuffer;
    renderbuffer.gen_buffers();
    renderbuffer.bind();
    renderbuffer.set_storage(GL_DEPTH24_STENCIL8, 1280, 640);
    renderbuffer.unbind();

    framebuffer.attach_renderbuffer(renderbuffer, GL_DEPTH_STENCIL_ATTACHMENT);

    if(!framebuffer.is_complete()) {
        std::cout << "Framebuffer creation failed" << std::endl;
        std::exit(-1);
    }

    framebuffer.unbind();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

    while(!window.is_close_requested()) {
        framebuffer.bind();
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        
        model = glm::rotate(model, 0.005f, glm::vec3(1.0f, 1.0f, 1.0f));

        shader.set_uniform_mat4("u_model", model);
        shader.set_uniform_mat4("u_view", view);
        shader.set_uniform_mat4("u_projection", projection);
        shader.set_uniform_int_array("u_textures", tex_slots, sizeof(tex_slots));
        shader.set_uniform_float("u_time", (f32) glfwGetTime());

        texture.bind();
        texture.activate(0);

        vao.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        vao.unbind();

        texture.unbind();

        shader.detach();

        gfx::Framebuffer::bind_default_framebuffer();
        glClear(GL_COLOR_BUFFER_BIT);

        screen_shader.use();

        screen_vao.bind();

        framebuffer.texture.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        screen_vao.unbind();

        screen_shader.detach();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(45.0f), (f32) width / (f32) height, 0.1f, 100.0f);
    win_dimensions.x = width;
    win_dimensions.y = height;
}