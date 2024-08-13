#include "GL/glew.h"
#include "TerrainRenderer.h"
#include "Utils/Math.h"

TerrainRenderer::TerrainRenderer(
  TerrainShader* shader,
  glm::mat4& projection_matrix
) {
  this->shader = shader;
  this->shader->start();
  this->shader->load_projection_matrix(projection_matrix);
  this->shader->connect_texture_units();
  this->shader->stop();
}

void TerrainRenderer::render(std::vector<Terrain*>& terrains) {
  for (Terrain* terrain : terrains) {
    prepare_terrain(terrain);

    load_model_matrix(terrain);

    glDrawElements(
      GL_TRIANGLES,
      terrain->get_model()->get_vertex_count(),
      GL_UNSIGNED_INT,
      0
    );

    unbind_terrain_model();
  }
}

void TerrainRenderer::prepare_terrain(Terrain* terrain) {
  RawModel* raw_model = terrain->get_model();
  glBindVertexArray(raw_model->get_vao_id());

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  this->bind_textures(terrain);
  this->shader->load_specular_lighting_variables(1, 0);
  // Todo: Add shine variables to terrain
}

void TerrainRenderer::bind_textures(Terrain* terrain) {
  TerrainTexturePack* texture_pack = terrain->get_texture_pack();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(
    GL_TEXTURE_2D,
    texture_pack->get_background_texture()->get_id()
  );

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture_pack->get_red_texture()->get_id());

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, texture_pack->get_green_texture()->get_id());

  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, texture_pack->get_blue_texture()->get_id());

  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, texture_pack->get_blend_map_texture()->get_id());
}

void TerrainRenderer::unbind_terrain_model() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void TerrainRenderer::load_model_matrix(Terrain* terrain) {
  glm::mat4 transformation_matrix = Math::create_transformation_matrix(
    glm::vec3(terrain->get_x(), 0, terrain->get_z()),
    glm::vec3(0, 0, 0),
    glm::vec3(1, 1, 1)
  );

  this->shader->load_transformation_matrix(transformation_matrix);
}
