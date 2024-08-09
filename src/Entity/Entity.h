#ifndef ENTITY_H
#define ENTITY_H

#include "Model/TexturedModel.h"
#include "math.h"
#include "glm/glm.hpp"

class Entity {
public:
  Entity(
    TexturedModel* model,
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale
  )
      : model(model), position(position), rotation(rotation), scale(scale) {}

  Entity(
    TexturedModel* model,
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale,
    int texture_index
  )
      : model(model), position(position), rotation(rotation), scale(scale),
        texture_index(texture_index) {}

  TexturedModel* get_model() const { return this->model; }
  glm::vec3 get_position() const { return this->position; }
  glm::vec3 get_rotation() const { return this->rotation; }
  glm::vec3 get_scale() const { return this->scale; }

  void set_model(TexturedModel* new_model) { this->model = new_model; }
  void set_position(glm::vec3 new_position) { this->position = new_position; }
  void set_rotation(glm::vec3 new_rotation) { this->rotation = new_rotation; }
  void set_scale(glm::vec3 new_scale) { this->scale = new_scale; }

  void change_position(glm::vec3 delta) { this->position += delta; }
  void change_rotation(glm::vec3 delta) { this->rotation += delta; }
  void change_scale(glm::vec3 delta) { this->scale += delta; }

  float get_texture_x_offset() {
    int row_count = this->model->get_texture()->get_row_count();
    int column = this->texture_index % row_count;

    return (float)column / (float)row_count;
  }

  float get_texture_y_offset() {
    int row_count = this->model->get_texture()->get_row_count();
    int row = this->texture_index / row_count;

    return (float)row / (float)row_count;
  }

private:
  TexturedModel* model;
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  int texture_index = 0;
};

#endif // !ENTITY_H
