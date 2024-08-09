#define GLM_ENABLE_EXPERIMENTAL

#include "Math.h"
#include "glm/gtx/transform.hpp"

glm::mat4 Math::create_transformation_matrix(
  glm::vec3 translation,
  glm::vec3 rotation,
  glm::vec3 scale
) {
  glm::mat4 translation_matrix = glm::translate(translation);

  glm::mat4 rotation_matrix =
    glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
    glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
    glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));

  glm::mat4 scale_matrix = glm::scale(scale);

  return translation_matrix * rotation_matrix * scale_matrix;
}

glm::mat4 Math::create_view_matrix(Camera* camera) {
  glm::mat4 view_matrix = glm::mat4(1.0f);
  view_matrix = glm::rotate(
    view_matrix,
    glm::radians(camera->get_pitch()),
    glm::vec3(1, 0, 0)
  );

  view_matrix = glm::rotate(
    view_matrix,
    glm::radians(camera->get_yaw()),
    glm::vec3(0, 1, 0)
  );

  glm::vec3 camera_position = camera->get_position();
  glm::vec3 inverse_camera_position =
    glm::vec3(-camera_position.x, -camera_position.y, -camera_position.z);
  view_matrix = glm::translate(view_matrix, inverse_camera_position);

  return view_matrix;
}

float Math::get_barry_centric_coordinate(
  glm::vec3 p1,
  glm::vec3 p2,
  glm::vec3 p3,
  glm::vec2 object_pos
) {
  float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
  float l1 = ((p2.z - p3.z) * (object_pos.x - p3.x) +
              (p3.x - p2.x) * (object_pos.y - p3.z)) /
             det;
  float l2 = ((p3.z - p1.z) * (object_pos.x - p3.x) +
              (p1.x - p3.x) * (object_pos.y - p3.z)) /
             det;
  float l3 = 1.0f - l1 - l2;

  return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
