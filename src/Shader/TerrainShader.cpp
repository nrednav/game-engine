#include "TerrainShader.h"
#include "Utils/Math.h"

TerrainShader::TerrainShader(std::string vertex_file, std::string fragment_file)
    : ShaderProgram(vertex_file, fragment_file) {
  this->bind_attributes();
  this->get_all_uniform_locations();
}

void TerrainShader::bind_attributes() {
  bind_attribute(0, "position");
  bind_attribute(1, "texture_coords");
  bind_attribute(2, "normal");
}

void TerrainShader::get_all_uniform_locations() {
  this->location_transformation_matrix =
    get_uniform_location("transformation_matrix");
  this->location_projection_matrix = get_uniform_location("projection_matrix");
  this->location_view_matrix = get_uniform_location("view_matrix");

  this->location_shine_damper = get_uniform_location("shine_damper");
  this->location_reflectivity = get_uniform_location("reflectivity");
  this->location_sky_color = get_uniform_location("sky_color");

  this->location_bg_texture = get_uniform_location("bg_texture");
  this->location_r_texture = get_uniform_location("r_texture");
  this->location_g_texture = get_uniform_location("g_texture");
  this->location_b_texture = get_uniform_location("b_texture");
  this->location_blend_map = get_uniform_location("blend_map");

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

void TerrainShader::load_transformation_matrix(glm::mat4 matrix) {
  load_matrix(this->location_transformation_matrix, matrix);
}

void TerrainShader::load_projection_matrix(glm::mat4 matrix) {
  load_matrix(this->location_projection_matrix, matrix);
}

void TerrainShader::load_view_matrix(Camera* camera) {
  glm::mat4 view_matrix = Math::create_view_matrix(camera);
  load_matrix(this->location_view_matrix, view_matrix);
}

void TerrainShader::load_lights(
  const std::vector<std::unique_ptr<Light>>& lights
) {
  for (int i = 0; i < MAX_LIGHT_COUNT; i++) {
    if (i < lights.size()) {
      load_vector(location_light_positions[i], lights[i]->get_position());
      load_vector(location_light_colors[i], lights[i]->get_color());
      load_vector(location_light_attenuations[i], lights[i]->get_attenuation());
    }
    else {
      load_vector(location_light_positions[i], glm::vec3(0, 0, 0));
      load_vector(location_light_colors[i], glm::vec3(0, 0, 0));
      load_vector(location_light_attenuations[i], glm::vec3(1, 0, 0));
    }
  }
}

void TerrainShader::load_specular_lighting_variables(
  float shine_damper,
  float reflectivity
) {
  load_float(this->location_shine_damper, shine_damper);
  load_float(this->location_reflectivity, reflectivity);
}

void TerrainShader::load_sky_color(glm::vec3 rgb) {
  load_vector(this->location_sky_color, rgb);
}

void TerrainShader::connect_texture_units() {
  load_int(location_bg_texture, 0);
  load_int(location_r_texture, 1);
  load_int(location_g_texture, 2);
  load_int(location_b_texture, 3);
  load_int(location_blend_map, 4);
}
