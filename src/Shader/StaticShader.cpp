#include "StaticShader.h"
#include "Utils/Math.h"

StaticShader::StaticShader(std::string vertex_file, std::string fragment_file)
    : ShaderProgram(vertex_file, fragment_file) {
  this->bind_attributes();
  this->get_all_uniform_locations();
}

void StaticShader::bind_attributes() {
  bind_attribute(0, "position");
  bind_attribute(1, "textureCoords");
  bind_attribute(2, "normal");
}

void StaticShader::get_all_uniform_locations() {
  this->location_transformation_matrix =
    get_uniform_location("transformation_matrix");
  this->location_projection_matrix = get_uniform_location("projection_matrix");
  this->location_view_matrix = get_uniform_location("view_matrix");
  this->location_shine_damper = get_uniform_location("shine_damper");
  this->location_reflectivity = get_uniform_location("reflectivity");
  this->location_use_fake_lighting = get_uniform_location("use_fake_lighting");
  this->location_sky_color = get_uniform_location("sky_color");

  this->location_texture_row_count = get_uniform_location("texture_row_count");
  this->location_texture_offset = get_uniform_location("textureOffset");

  this->location_light_positions = std::vector<int>(MAX_LIGHT_COUNT);
  this->location_light_colors = std::vector<int>(MAX_LIGHT_COUNT);
  this->location_light_attenuations = std::vector<int>(MAX_LIGHT_COUNT);

  for (int i = 0; i < MAX_LIGHT_COUNT; i++) {
    this->location_light_positions[i] =
      get_uniform_location("light_position[" + std::to_string(i) + "]");
    this->location_light_colors[i] =
      get_uniform_location("light_color[" + std::to_string(i) + "]");
    this->location_light_attenuations[i] =
      get_uniform_location("light_attenuation[" + std::to_string(i) + "]");
  }
}

void StaticShader::load_transformation_matrix(glm::mat4 matrix) {
  load_matrix(this->location_transformation_matrix, matrix);
}

void StaticShader::load_projection_matrix(glm::mat4 matrix) {
  load_matrix(this->location_projection_matrix, matrix);
}

void StaticShader::load_view_matrix(Camera* camera) {
  glm::mat4 view_matrix = Math::create_view_matrix(camera);
  load_matrix(this->location_view_matrix, view_matrix);
}

void StaticShader::load_lights(std::vector<Light*> lights) {
  for (int i = 0; i < MAX_LIGHT_COUNT; i++) {
    if (i < lights.size()) {
      load_vector(location_light_positions[i], lights[i]->get_position());
      load_vector(location_light_colors[i], lights[i]->get_color());
      load_vector(location_light_attenuations[i], lights[i]->get_attenuation());
    } else {
      load_vector(location_light_positions[i], glm::vec3(0, 0, 0));
      load_vector(location_light_colors[i], glm::vec3(0, 0, 0));
      load_vector(location_light_attenuations[i], glm::vec3(1, 0, 0));
    }
  }
}

void StaticShader::load_specular_lighting_variables(
  float shine_damper,
  float reflectivity
) {
  load_float(this->location_shine_damper, shine_damper);
  load_float(this->location_reflectivity, reflectivity);
}

void StaticShader::load_fake_lighting_variable(bool value) {
  load_bool(this->location_use_fake_lighting, value);
}

void StaticShader::load_sky_color(glm::vec3 rgb) {
  load_vector(this->location_sky_color, rgb);
}

void StaticShader::load_texture_row_count(int texture_row_count) {
  load_float(location_texture_row_count, (float)texture_row_count);
}

void StaticShader::load_texture_offset(float x, float y) {
  load_vector2d(location_texture_offset, glm::vec2(x, y));
}
