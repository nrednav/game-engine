#include "Player.h"
#include "GLFW/glfw3.h"
#include "Display/DisplayManager.h"
#include "Constants.h"
#include "math.h"

Player::Player(TexturedModel* model, glm::vec3 position, glm::vec3 rotation,
               glm::vec3 scale)
    : Entity(model, position, rotation, scale) {}

void Player::move(Terrain* terrain) {
  this->detectInput();

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    this->currentSpeed *= 5;
  }

  float frameTimeSeconds =
      (float)DisplayManager::get_instance()->get_frame_time_seconds();

  glm::vec3 lastSafePos = this->get_position();

  // Horizontal Movement
  this->change_rotation(
      glm::vec3(0, this->currentTurnSpeed * frameTimeSeconds, 0));
  float distance = this->currentSpeed * frameTimeSeconds;
  float dx = distance * glm::sin(glm::radians(this->get_rotation().y));
  float dz = distance * glm::cos(glm::radians(this->get_rotation().y));

  bool xOutOfBounds = dx + this->get_position().x >= TERRAIN_SIZE ||
                      dx + this->get_position().x <= -TERRAIN_SIZE;
  bool zOutOfBounds = dz + this->get_position().z >= TERRAIN_SIZE ||
                      dz + this->get_position().z <= -TERRAIN_SIZE;

  if (xOutOfBounds || zOutOfBounds)
    this->set_position(lastSafePos);
  else
    this->change_position(glm::vec3(dx, 0, dz));

  // Vertical Movement (E.g. jump)
  this->verticalSpeed += PLAYER_GRAVITY * frameTimeSeconds;
  this->change_position(
      glm::vec3(0, this->verticalSpeed * frameTimeSeconds, 0));

  float terrainHeight = terrain->getTerrainHeightAt(this->get_position().x,
                                                    this->get_position().z);

  if (this->get_position().y < terrainHeight) {
    this->verticalSpeed = 0;
    this->isAirborne = false;
    this->set_position(glm::vec3(this->get_position().x, terrainHeight,
                                 this->get_position().z));
  }
}

void Player::jump() {
  if (!this->isAirborne) {
    this->verticalSpeed = JUMP_FORCE;
    this->isAirborne = true;
  }
}

void Player::detectInput() {
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
    this->currentSpeed = PLAYER_RUN_SPEED;
  else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
    this->currentSpeed = -PLAYER_RUN_SPEED;
  else
    this->currentSpeed = 0;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
    this->currentTurnSpeed = -PLAYER_TURN_SPEED;
  else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
    this->currentTurnSpeed = PLAYER_TURN_SPEED;
  else
    this->currentTurnSpeed = 0;

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
    this->jump();
}
