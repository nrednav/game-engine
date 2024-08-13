#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

class Light {
public:
  Light(glm::vec3 position, glm::vec3 color)
      : position(position), color(color) {}

  Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation)
      : position(position), color(color), attenuation(attenuation) {}

  glm::vec3 get_position() const { return this->position; }
  glm::vec3 get_color() const { return this->color; }
  glm::vec3 get_attenuation() const { return this->attenuation; }

  void set_position(glm::vec3 position) { this->position = position; }
  void set_color(glm::vec3 color) { this->color = color; }
  void set_attenuation(glm::vec3 attenuation) {
    this->attenuation = attenuation;
  }

private:
  glm::vec3 position;
  glm::vec3 color;
  glm::vec3 attenuation = glm::vec3(1, 0, 0);
};

#endif // !LIGHT_H
