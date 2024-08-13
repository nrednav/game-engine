#define GLM_ENABLE_EXPERIMENTAL

#include "SkyboxShader.h"
#include "Constants.h"
#include "Utils/Math.h"
#include "glm/gtx/transform.hpp"

SkyboxShader::SkyboxShader(
  std::string vertex_file,
  std::string fragment_file,
  Display* display
)
    : ShaderProgram(vertex_file, fragment_file) {
  this->display = display;
  this->bind_attributes();
  this->get_all_uniform_locations();
}

void SkyboxShader::bind_attributes() {
  bind_attribute(0, "position");
}

void SkyboxShader::get_all_uniform_locations() {
  this->location_projection_matrix = get_uniform_location("projection_matrix");
  this->location_view_matrix = get_uniform_location("view_matrix");
  this->location_fog_color = get_uniform_location("fog_color");
  this->location_day_cube_map = get_uniform_location("day_cube_map");
  this->location_night_cube_map = get_uniform_location("night_cube_map");
  this->location_blend_factor = get_uniform_location("blend_factor");
}

void SkyboxShader::load_projection_matrix(glm::mat4 matrix) {
  load_matrix(this->location_projection_matrix, matrix);
}

void SkyboxShader::load_view_matrix(Camera* camera) {
  glm::mat4 view_matrix = Math::create_view_matrix(camera);

  view_matrix[3][0] = 0;
  view_matrix[3][1] = 0;
  view_matrix[3][2] = 0;

  this->current_rotation +=
    SKYBOX_ROTATION_SPEED * this->display->get_frame_time_seconds();

  view_matrix = glm::rotate(
    view_matrix,
    glm::radians(this->current_rotation),
    glm::vec3(0, 1, 0)
  );

  load_matrix(this->location_view_matrix, view_matrix);
}

void SkyboxShader::load_fog_color(glm::vec3 color) {
  load_vector(this->location_fog_color, color);
}

void SkyboxShader::load_blend_factor(float value) {
  load_float(this->location_blend_factor, value);
}

void SkyboxShader::connect_texture_units() {
  load_int(this->location_day_cube_map, 0);
  load_int(this->location_night_cube_map, 1);
}
