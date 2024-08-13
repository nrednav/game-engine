#include "GL/glew.h"
#include "SkyboxRenderer.h"

#include "glm/gtc/constants.hpp"

SkyboxRenderer::SkyboxRenderer(
  SkyboxShader* shader,
  Loader* loader,
  glm::mat4 projection_matrix,
  Display* display
) {
  this->display = display;
  this->cube = loader->load_to_vao(this->vertices, 3);
  this->day_texture_id = loader->load_cube_map(this->day_texture_filepaths);
  this->night_texture_id = loader->load_cube_map(this->night_texture_filepaths);
  this->shader = shader;

  this->shader->start();
  this->shader->connect_texture_units();
  this->shader->load_projection_matrix(projection_matrix);
  this->shader->stop();
}

void SkyboxRenderer::render(Camera* camera, glm::vec3 color) {
  this->shader->start();
  this->shader->load_view_matrix(camera);
  this->shader->load_fog_color(color);

  glBindVertexArray(this->cube->get_vao_id());
  glEnableVertexAttribArray(0);

  this->bind_textures();
  glDrawArrays(GL_TRIANGLES, 0, this->cube->get_vertex_count());

  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
  this->shader->stop();
}

void SkyboxRenderer::bind_textures() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->day_texture_id);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->night_texture_id);

  this->shader->load_blend_factor(this->get_blend_factor());
}

float SkyboxRenderer::get_blend_factor() {
  this->time += this->display->get_frame_time_seconds();
  float delta = -1 * this->time * 2 * glm::pi<float>() / SKYBOX_CYCLE_LENGTH;

  return (float)glm::abs(0.5f * glm::cos(glm::radians(delta)) - 0.5f);
}
