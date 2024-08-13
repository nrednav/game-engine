#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "Display/Display.h"
#include "Shader/ShaderProgram.h"
#include "Entity/Camera.h"

class SkyboxShader : public ShaderProgram {
public:
  SkyboxShader(
    std::string vertex_file,
    std::string fragment_file,
    Display* display
  );
  void load_projection_matrix(glm::mat4 matrix);
  void load_view_matrix(Camera* camera);
  void load_fog_color(glm::vec3 color);
  void load_blend_factor(float value);
  void connect_texture_units();

public:
  void bind_attributes();
  void get_all_uniform_locations();

private:
  Display* display;

  int location_projection_matrix;
  int location_view_matrix;
  int location_fog_color;
  int location_day_cube_map;
  int location_night_cube_map;
  int location_blend_factor;

  float current_rotation = 0.0f;
};

#endif // !SKYBOXSHADER_H
