#include <vector>

#include "shader.hpp"

using namespace gfx;

Shader::Shader(std::string vertex_file_path, std::string fragment_file_path) {
    vertex_handle = glCreateShader(GL_VERTEX_SHADER);
    fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertex_source = util::read_file(vertex_file_path);
    std::string fragment_source = util::read_file(fragment_file_path);

    GLint result = GL_FALSE;
    int info_log_length;

    printf("Compiling shader %s\n", vertex_file_path.c_str());
    const char *vertex_source_pointer = vertex_source.c_str();
    glShaderSource(vertex_handle, 1, &vertex_source_pointer, NULL);
    glCompileShader(vertex_handle);

    glGetShaderiv(vertex_handle, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_handle, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
	std::vector<char> vertex_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(vertex_handle, info_log_length, NULL, &vertex_shader_error_message[0]);
        fprintf(stderr, "%s\n", &vertex_shader_error_message[0]);
    }

    
    printf("Compiling shader %s\n", fragment_file_path.c_str());
    const char *fragment_source_pointer = fragment_source.c_str();
    glShaderSource(fragment_handle, 1, &fragment_source_pointer, NULL);
    glCompileShader(fragment_handle);

    glGetShaderiv(fragment_handle, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_handle, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
	std::vector<char> fragment_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(fragment_handle, info_log_length, NULL, &fragment_shader_error_message[0]);
        fprintf(stderr, "%s\n", &fragment_shader_error_message[0]);
    }

    printf("Linking shader\n");
    handle = glCreateProgram();
    glAttachShader(handle, vertex_handle);
    glAttachShader(handle, fragment_handle);
    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, &result);
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
	    std::vector<char> program_error_message(info_log_length + 1);
	    glGetProgramInfoLog(handle, info_log_length, NULL, &program_error_message[0]);
	    printf("%s\n", &program_error_message[0]);
    }

    glDetachShader(handle, vertex_handle);
    glDetachShader(handle, fragment_handle);

    glDeleteShader(vertex_handle);
    glDeleteShader(fragment_handle);
}

void Shader::use(void) {
    glUseProgram(handle);
}

void Shader::detach(void) {
    glUseProgram(0);
}

void Shader::set_uniform_int(std::string location, i32 value) {
    glUniform1i(glGetUniformLocation(handle, location.c_str()), value);
}

void Shader::set_uniform_float(std::string location, f32 value) {
    glUniform1f(glGetUniformLocation(handle, location.c_str()), value);
}

void Shader::set_uniform_int_array(std::string location, const i32 *value, size_t count) {
    glUniform1iv(glGetUniformLocation(handle, location.c_str()), count, (const GLint*) value);
}

void Shader::set_uniform_mat4(std::string location, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(handle, location.c_str()), 1, false, glm::value_ptr(value));
}

void Shader::set_uniform_vec3(std::string location, glm::vec3 value) {
    glUniform3f(glGetUniformLocation(handle, location.c_str()), value.x, value.y, value.z);
}

void Shader::set_uniform_ivec2(std::string location, glm::ivec2 value) {
    glUniform2i(glGetUniformLocation(handle, location.c_str()), value.x, value.y);
}

Shader::~Shader(void) {
    glDeleteProgram(this->handle);
}