#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glm/glm.hpp>
#include <string>

class ShaderProgram {
public:
  ShaderProgram(std::string vertex_file_path, std::string fragment_file_path);

  void start();
  void stop();
  void cleanup();
  static int load_shader(std::string source, int type);

  int get_uniform_location(std::string uniform_name);

protected:
  virtual void bind_attributes() = 0;
  virtual void get_all_uniform_locations() = 0;
  void bind_attribute(int attribute, std::string variable_name);

  void load_int(int location, int value);
  void load_float(int location, float value);
  void load_vector(int location, glm::vec3 vector);
  void load_vector2d(int location, glm::vec2 vector);
  void load_bool(int location, bool value);
  void load_matrix(int location, glm::mat4 matrix);

private:
  unsigned int program_id;
  unsigned int vertex_shader_id;
  unsigned int fragment_shader_id;

  static bool has_errors(unsigned int shader_id, int type);
};

#endif // !SHADERPROGRAM_H
