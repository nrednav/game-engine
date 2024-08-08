#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"

class Camera {
public:
  Camera(Player* player, glm::vec3 position);

  glm::vec3 getPosition() const { return this->position; }
  float getPitch() const { return this->pitch; }
  float getYaw() const { return this->yaw; }
  float getRoll() const { return this->roll; }

  void move();

private:
  glm::vec3 position = glm::vec3(0, 0, 0);

  float pitch = 15.0f;
  float yaw = 0.0f;
  float roll = 0.0f;

  float distanceFromPlayer = 30.0f;
  float angleAroundPlayer = 0.0f;

  float lastZoomLevel;
  float zoomLevel;

  Player* player;

  void calculateZoom();
  void calculatePitch();
  void calculateAngleAroundPlayer();

  float calculateHorizontalDistance();
  float calculateVerticalDistance();
  void calculateCameraPosition(const float& horizontalDistance,
                               const float& verticalDistance);
};

#endif // !CAMERA_H
