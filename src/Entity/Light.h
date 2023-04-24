#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

class Light {
public:
  Light(glm::vec3 position, glm::vec3 color)
      : position(position), color(color) {}

  Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation)
      : position(position), color(color), attenuation(attenuation) {}

  glm::vec3 getPosition() const { return this->position; }
  glm::vec3 getColor() const { return this->color; }
  glm::vec3 getAttenuation() const { return this->attenuation; }

  void setPosition(glm::vec3 position) { this->position = position; }
  void setColor(glm::vec3 color) { this->color = color; }
  void setAttenuation(glm::vec3 attenuation) {
    this->attenuation = attenuation;
  }

private:
  glm::vec3 position;
  glm::vec3 color;
  glm::vec3 attenuation = glm::vec3(1, 0, 0);
};

#endif // !LIGHT_H
