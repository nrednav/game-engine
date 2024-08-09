#ifndef MATH_H
#define MATH_H

#include "Entity/Camera.h"
#include "glm/glm.hpp"

class Math {
public:
  static glm::mat4 create_transformation_matrix(
    glm::vec3 translation,
    glm::vec3 rotation,
    glm::vec3 scale
  );

  static glm::mat4 create_view_matrix(Camera* camera);

  static float get_barry_centric_coordinate(
    glm::vec3 p1,
    glm::vec3 p2,
    glm::vec3 p3,
    glm::vec2 object_pos
  );
};

#endif // !MATH_H
