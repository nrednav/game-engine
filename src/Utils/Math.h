#ifndef MATH_H
#define MATH_H

#include "Entity/Camera.h"
#include "glm/glm.hpp"

class Math {
public:
  static glm::mat4 createTransformationMatrix(glm::vec3 translation,
                                              glm::vec3 rotation,
                                              glm::vec3 scale);

  static glm::mat4 createViewMatrix(Camera *camera);

  static float getBarryCentricCoordinate(glm::vec3 p1, glm::vec3 p2,
                                         glm::vec3 p3, glm::vec2 objectPos);
};

#endif // !MATH_H
