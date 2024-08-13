#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"

#include <vector>

class TerrainShader : public ShaderProgram {
public:
  TerrainShader(std::string vertex_file, std::string fragment_file);
  void load_transformation_matrix(glm::mat4 matrix);
  void load_projection_matrix(glm::mat4 matrix);
  void load_view_matrix(Camera* camera);
  void load_lights(const std::vector<std::unique_ptr<Light>>& lights);
  void load_specular_lighting_variables(float shine_damper, float reflectivity);
  void load_sky_color(glm::vec3 rgb);
  void connect_texture_units();

public:
  void bind_attributes();
  void get_all_uniform_locations();

private:
  const int MAX_LIGHT_COUNT = 4;
  std::vector<int> location_light_positions;
  std::vector<int> location_light_colors;
  std::vector<int> location_light_attenuations;

  int location_transformation_matrix;
  int location_projection_matrix;
  int location_view_matrix;

  int location_shine_damper;
  int location_reflectivity;
  int location_sky_color;

  int location_bg_texture;
  int location_r_texture;
  int location_g_texture;
  int location_b_texture;
  int location_blend_map;
};

#endif // !TERRAINSHADER_H
