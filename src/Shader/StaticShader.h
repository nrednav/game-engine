#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"

#include <vector>

class StaticShader : public ShaderProgram {
public:
  StaticShader(std::string vertex_file, std::string fragment_file);
  void load_transformation_matrix(glm::mat4 matrix);
  void load_projection_matrix(glm::mat4 matrix);
  void load_view_matrix(Camera* camera);
  void load_lights(std::vector<Light*> lights);
  void load_specular_lighting_variables(float shineDamper, float reflectivity);
  void load_fake_lighting_variable(bool value);
  void load_sky_color(glm::vec3 rgb);
  void load_texture_row_count(int row_count);
  void load_texture_offset(float x, float y);

public:
  void bind_attributes();
  void get_all_uniform_locations();

private:
  const int MAX_LIGHT_COUNT = 21;
  std::vector<int> location_light_positions;
  std::vector<int> location_light_colors;
  std::vector<int> location_light_attenuations;

  int location_transformation_matrix;
  int location_projection_matrix;
  int location_view_matrix;
  int location_shine_damper;
  int location_reflectivity;
  int location_use_fake_lighting;
  int location_sky_color;
  int location_texture_row_count;
  int location_texture_offset;
};

#endif // !STATICSHADER_H
