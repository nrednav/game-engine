#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "Entity/Entity.h"
#include "Shader/StaticShader.h"

#include <map>
#include <vector>

class EntityRenderer {
public:
  EntityRenderer(StaticShader* shader, glm::mat4& projectionMatrix);
  void render(std::map<TexturedModel*, std::vector<Entity*>>& entities);

private:
  StaticShader* shader;

  void prepareTexturedModel(TexturedModel* model);
  void unbindTexturedModel();
  void prepareEntity(Entity* entity);
};

#endif // !ENTITYRENDERER_H
