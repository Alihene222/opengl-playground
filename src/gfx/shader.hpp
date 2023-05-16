#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>

#include "gfx.hpp"
#include "util/util.hpp"

namespace gfx {

struct Shader {
    GLuint handle;
    GLuint vertex_handle;
    GLuint fragment_handle;

    Shader() = default;

    Shader(std::string vertex_file_path, std::string fragment_file_path);

    ~Shader(void);

    void use(void);

    void detach(void);
    
    void set_uniform_int(std::string location, i32 value);

    void set_uniform_float(std::string location, f32 value);

    void set_uniform_int_array(std::string location, const i32 *value, size_t count);

    void set_uniform_mat4(std::string location, glm::mat4 value);

    void set_uniform_vec3(std::string location, glm::vec3 value);

    void set_uniform_ivec2(std::string location, glm::ivec2 value);
};

}

#endif
