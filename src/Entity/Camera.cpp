#include "Camera.h"
#include "Constants.h"
#include <GLFW/glfw3.h>

Camera::Camera(Player* player, glm::vec3 position)
    : position(position), player(player) {}

void Camera::move() {
  this->calculateZoom();
  this->calculatePitch();
  this->calculateAngleAroundPlayer();
  float horizontalDistance = this->calculateHorizontalDistance();
  float verticalDistance = this->calculateVerticalDistance();
  this->calculateCameraPosition(horizontalDistance, verticalDistance);
  this->yaw = 180 - (this->player->getRotation().y + this->angleAroundPlayer);
  this->yaw = fmodf(this->yaw, 360.0f);
}

void Camera::calculateZoom() {
  int equalPressed =
      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_EQUAL) == GLFW_PRESS;
  int minusPressed =
      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_MINUS) == GLFW_PRESS;
  int leftShiftPressed =
      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

  if (leftShiftPressed && equalPressed)
    this->distanceFromPlayer -= CAMERA_ZOOM_LEVEL;

  if (leftShiftPressed && minusPressed)
    this->distanceFromPlayer -= -CAMERA_ZOOM_LEVEL;
}

void Camera::calculatePitch() {
  float deltaPitch = 0.0f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
    deltaPitch = -PLAYER_TURN_SPEED * 0.01f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
    deltaPitch = PLAYER_TURN_SPEED * 0.01f;

  this->pitch -= deltaPitch;

  if (this->pitch < 0)
    pitch = 0;
  else if (this->pitch > 90)
    pitch = 90;
}

void Camera::calculateAngleAroundPlayer() {
  float deltaAngle = 0.0f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
    deltaAngle = -PLAYER_TURN_SPEED * 0.03f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    deltaAngle = PLAYER_TURN_SPEED * 0.03f;

  this->angleAroundPlayer -= deltaAngle;
}

float Camera::calculateHorizontalDistance() {
  float hd = this->distanceFromPlayer * glm::cos(glm::radians(this->pitch));
  return (hd < 0) ? 0 : hd;
}

float Camera::calculateVerticalDistance() {
  float vd = this->distanceFromPlayer * glm::sin(glm::radians(this->pitch));
  return (vd < 0) ? 0 : vd;
}

void Camera::calculateCameraPosition(const float& horizontalDistance,
                                     const float& verticalDistance) {
  float theta = this->player->getRotation().y + this->angleAroundPlayer;
  float xOffset = horizontalDistance * glm::sin(glm::radians(theta));
  float zOffset = horizontalDistance * glm::cos(glm::radians(theta));

  this->position.x = this->player->getPosition().x - xOffset;
  this->position.z = this->player->getPosition().z - zOffset;
  this->position.y = this->player->getPosition().y + verticalDistance + 5.0f;
}
