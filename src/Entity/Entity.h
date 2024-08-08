#ifndef ENTITY_H
#define ENTITY_H

#include "Model/TexturedModel.h"
#include "math.h"
#include "glm/glm.hpp"

class Entity {
public:
  Entity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation,
         glm::vec3 scale)
      : model(model), position(position), rotation(rotation), scale(scale) {}

  Entity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation,
         glm::vec3 scale, int textureIndex)
      : model(model), position(position), rotation(rotation), scale(scale),
        textureIndex(textureIndex) {}

  TexturedModel* getModel() const { return this->model; }
  glm::vec3 getPosition() const { return this->position; }
  glm::vec3 getRotation() const { return this->rotation; }
  glm::vec3 getScale() const { return this->scale; }

  void setModel(TexturedModel* newModel) { this->model = newModel; }
  void setPosition(glm::vec3 newPosition) { this->position = newPosition; }
  void setRotation(glm::vec3 newRotation) { this->rotation = newRotation; }
  void setScale(glm::vec3 newScale) { this->scale = newScale; }

  void changePosition(glm::vec3 delta) { this->position += delta; }
  void changeRotation(glm::vec3 delta) { this->rotation += delta; }
  void changeScale(glm::vec3 delta) { this->scale += delta; }

  float getTextureXOffset() {
    int numOfRows = this->model->getTexture()->getNumberOfRows();
    int column = this->textureIndex % numOfRows;
    return (float)column / (float)numOfRows;
  }

  float getTextureYOffset() {
    int numOfRows = this->model->getTexture()->getNumberOfRows();
    int row = this->textureIndex / numOfRows;
    return (float)row / (float)numOfRows;
  }

private:
  TexturedModel* model;
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  int textureIndex = 0;
};

#endif // !ENTITY_H
