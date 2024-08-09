#include "GL/glew.h"
#include "ShaderProgram.h"

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(
  std::string vertex_file_path,
  std::string fragment_file_path
) {
  this->vertex_shader_id = load_shader(vertex_file_path, GL_VERTEX_SHADER);
  this->fragment_shader_id =
    load_shader(fragment_file_path, GL_FRAGMENT_SHADER);
  this->program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);
  glValidateProgram(program_id);
}

void ShaderProgram::start() {
  glUseProgram(this->program_id);
}

void ShaderProgram::stop() {
  glUseProgram(0);
}

void ShaderProgram::cleanup() {
  stop();
  glDetachShader(this->program_id, this->vertex_shader_id);
  glDetachShader(this->program_id, this->fragment_shader_id);
  glDeleteShader(this->vertex_shader_id);
  glDeleteShader(this->fragment_shader_id);
  glDeleteProgram(this->program_id);
}

int ShaderProgram::load_shader(std::string source, int type) {
  std::string shader_source, line;
  std::ifstream shader_file(source);

  while (std::getline(shader_file, line)) {
    shader_source += line + "\n";
  }

  const GLchar* shader_code = shader_source.c_str();

  unsigned int shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, &shader_code, NULL);
  glCompileShader(shader_id);

  return has_errors(shader_id, type) ? -1 : shader_id;
}

void ShaderProgram::bind_attribute(int attribute, std::string variable_name) {
  glBindAttribLocation(
    this->program_id,
    attribute,
    (const GLchar*)variable_name.c_str()
  );
}

int ShaderProgram::get_uniform_location(std::string uniform_name) {
  return glGetUniformLocation(
    this->program_id,
    (const GLchar*)uniform_name.c_str()
  );
}

bool ShaderProgram::has_errors(unsigned int shader_id, int type) {
  int success;
  char info_log[512];
  std::string shader_type = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader_id, 1024, NULL, info_log);

    std::cout << "ERROR::SHADER_COMPILATION_ERROR::" << shader_type << "\n"
              << info_log << std::endl;

    return true;
  }

  return false;
}

// Uniform methods
void ShaderProgram::load_int(int location, int value) {
  glUniform1i(location, value);
}

void ShaderProgram::load_float(int location, float value) {
  glUniform1f(location, value);
}

void ShaderProgram::load_vector(int location, glm::vec3 vector) {
  glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::load_vector2d(int location, glm::vec2 vector) {
  glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::load_bool(int location, bool value) {
  glUniform1f(location, value ? 1.0f : 0.0f);
}

void ShaderProgram::load_matrix(int location, glm::mat4 matrix) {
  glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
}
