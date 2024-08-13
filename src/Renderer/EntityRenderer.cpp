#include "GL/glew.h"
#include "MasterRenderer.h"
#include "EntityRenderer.h"
#include "Utils/Math.h"

EntityRenderer::EntityRenderer(
  StaticShader* shader,
  glm::mat4& projection_matrix
) {
  this->shader = shader;
  shader->start();
  shader->load_projection_matrix(projection_matrix);
  shader->stop();
}

void EntityRenderer::render(
  std::map<TexturedModel*, std::vector<Entity*>>& entities
) {
  for (auto& entry : entities) {
    TexturedModel* model = entry.first;
    std::vector<Entity*> entitiesBatch = entry.second;

    prepare_textured_model(model);

    for (Entity* entity : entitiesBatch) {
      prepare_entity(entity);

      glDrawElements(
        GL_TRIANGLES,
        model->get_raw_model()->get_vertex_count(),
        GL_UNSIGNED_INT,
        0
      );
    }

    unbind_textured_model();
  }
}

void EntityRenderer::prepare_textured_model(TexturedModel* model) {
  RawModel* raw_model = model->get_raw_model();
  glBindVertexArray(raw_model->get_vao_id());

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  ModelTexture* texture = model->get_texture();
  this->shader->load_texture_row_count(texture->get_row_count());

  if (texture->has_transparency()) {
    MasterRenderer::disable_culling();
  }

  this->shader->load_fake_lighting_variable(texture->uses_fake_lighting());
  this->shader->load_specular_lighting_variables(
    texture->get_shine_damper(),
    texture->get_reflectivity()
  );

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->get_id());
}

void EntityRenderer::unbind_textured_model() {
  MasterRenderer::enable_culling();
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void EntityRenderer::prepare_entity(Entity* entity) {
  glm::mat4 transformation_matrix = Math::create_transformation_matrix(
    entity->get_position(),
    entity->get_rotation(),
    entity->get_scale()
  );

  this->shader->load_transformation_matrix(transformation_matrix);

  this->shader->load_texture_offset(
    entity->get_texture_x_offset(),
    entity->get_texture_y_offset()
  );
}
