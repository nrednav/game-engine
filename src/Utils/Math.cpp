#define GLM_ENABLE_EXPERIMENTAL

#include "Math.h"
#include "glm/gtx/transform.hpp"

glm::mat4 Math::createTransformationMatrix(glm::vec3 translation,
                                           glm::vec3 rotation,
                                           glm::vec3 scale) {
  glm::mat4 translationMatrix = glm::translate(translation);
  glm::mat4 rotationMatrix =
      glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
      glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
      glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
  glm::mat4 scaleMatrix = glm::scale(scale);

  return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Math::createViewMatrix(Camera* camera) {
  glm::mat4 viewMatrix = glm::mat4(1.0f);
  viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->get_pitch()),
                           glm::vec3(1, 0, 0));

  viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->get_yaw()),
                           glm::vec3(0, 1, 0));

  glm::vec3 cameraPosition = camera->get_position();
  glm::vec3 inverseCameraPosition =
      glm::vec3(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z);
  viewMatrix = glm::translate(viewMatrix, inverseCameraPosition);

  return viewMatrix;
}

float Math::getBarryCentricCoordinate(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
                                      glm::vec2 objectPos) {
  float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
  float l1 = ((p2.z - p3.z) * (objectPos.x - p3.x) +
              (p3.x - p2.x) * (objectPos.y - p3.z)) /
             det;
  float l2 = ((p3.z - p1.z) * (objectPos.x - p3.x) +
              (p1.x - p3.x) * (objectPos.y - p3.z)) /
             det;
  float l3 = 1.0f - l1 - l2;

  return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
