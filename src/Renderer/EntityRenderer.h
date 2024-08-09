#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "Entity/Entity.h"
#include "Shader/StaticShader.h"

#include <map>
#include <vector>

class EntityRenderer {
public:
  EntityRenderer(StaticShader* shader, glm::mat4& projection_matrix);
  void render(std::map<TexturedModel*, std::vector<Entity*>>& entities);

private:
  StaticShader* shader;

  void prepare_textured_model(TexturedModel* model);
  void unbind_textured_model();
  void prepare_entity(Entity* entity);
};

#endif // !ENTITYRENDERER_H
