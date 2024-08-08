#include "Camera.h"
#include "Constants.h"
#include <GLFW/glfw3.h>

Camera::Camera(Player* player, glm::vec3 position)
    : position(position), player(player) {}

void Camera::move() {
  this->calculate_zoom();
  this->calculate_pitch();
  this->calculate_angle_around_player();

  float horizontal_distance = this->calculate_horizontal_distance();
  float vertical_distance = this->calculate_vertical_distance();

  this->calculate_camera_position(horizontal_distance, vertical_distance);
  this->yaw =
      180 - (this->player->get_rotation().y + this->angle_around_player);
  this->yaw = fmodf(this->yaw, 360.0f);
}

void Camera::calculate_zoom() {
  int equal_pressed =
      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_EQUAL) == GLFW_PRESS;
  int minus_pressed =
      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_MINUS) == GLFW_PRESS;
  int left_shift_pressed =
      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

  if (left_shift_pressed && equal_pressed)
    this->distance_from_player -= CAMERA_ZOOM_LEVEL;

  if (left_shift_pressed && minus_pressed)
    this->distance_from_player -= -CAMERA_ZOOM_LEVEL;
}

void Camera::calculate_pitch() {
  float delta_pitch = 0.0f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
    delta_pitch = -PLAYER_TURN_SPEED * 0.01f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
    delta_pitch = PLAYER_TURN_SPEED * 0.01f;

  this->pitch -= delta_pitch;

  if (this->pitch < 0)
    pitch = 0;
  else if (this->pitch > 90)
    pitch = 90;
}

void Camera::calculate_angle_around_player() {
  float delta_angle = 0.0f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
    delta_angle = -PLAYER_TURN_SPEED * 0.03f;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    delta_angle = PLAYER_TURN_SPEED * 0.03f;

  this->angle_around_player -= delta_angle;
}

float Camera::calculate_horizontal_distance() {
  float horizontal_distance =
      this->distance_from_player * glm::cos(glm::radians(this->pitch));
  return (horizontal_distance < 0) ? 0 : horizontal_distance;
}

float Camera::calculate_vertical_distance() {
  float vertical_distance =
      this->distance_from_player * glm::sin(glm::radians(this->pitch));
  return (vertical_distance < 0) ? 0 : vertical_distance;
}

void Camera::calculate_camera_position(const float& horizontal_distance,
                                       const float& vertical_distance) {
  float theta = this->player->get_rotation().y + this->angle_around_player;
  float x_offset = horizontal_distance * glm::sin(glm::radians(theta));
  float z_offset = horizontal_distance * glm::cos(glm::radians(theta));

  this->position.x = this->player->get_position().x - x_offset;
  this->position.z = this->player->get_position().z - z_offset;
  this->position.y = this->player->get_position().y + vertical_distance + 5.0f;
}
