#include "Player.h"
#include "GLFW/glfw3.h"
#include "Constants.h"
#include "math.h"

Player::Player(
  TexturedModel* model,
  glm::vec3 position,
  glm::vec3 rotation,
  glm::vec3 scale
)
    : Entity(model, position, rotation, scale) {}

void Player::move(Terrain* terrain, double frame_time_seconds) {
  this->detect_input();

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    this->current_speed *= 5;
  }

  glm::vec3 last_safe_position = this->get_position();

  // Horizontal Movement
  this->change_rotation(
    glm::vec3(0, this->current_turn_speed * frame_time_seconds, 0)
  );
  float distance = this->current_speed * frame_time_seconds;
  float dx = distance * glm::sin(glm::radians(this->get_rotation().y));
  float dz = distance * glm::cos(glm::radians(this->get_rotation().y));

  bool x_out_of_bounds = dx + this->get_position().x >= TERRAIN_SIZE ||
                         dx + this->get_position().x <= -TERRAIN_SIZE;
  bool z_out_of_bounds = dz + this->get_position().z >= TERRAIN_SIZE ||
                         dz + this->get_position().z <= -TERRAIN_SIZE;

  if (x_out_of_bounds || z_out_of_bounds) {
    this->set_position(last_safe_position);
  }
  else {
    this->change_position(glm::vec3(dx, 0, dz));
  }

  // Vertical Movement (E.g. jump)
  this->vertical_speed += PLAYER_GRAVITY * frame_time_seconds;
  this->change_position(
    glm::vec3(0, this->vertical_speed * frame_time_seconds, 0)
  );

  float terrain_height = terrain->get_terrain_height_at(
    this->get_position().x,
    this->get_position().z
  );

  if (this->get_position().y < terrain_height) {
    this->vertical_speed = 0;
    this->is_airborne = false;
    this->set_position(
      glm::vec3(this->get_position().x, terrain_height, this->get_position().z)
    );
  }
}

void Player::jump() {
  if (!this->is_airborne) {
    this->vertical_speed = JUMP_FORCE;
    this->is_airborne = true;
  }
}

void Player::detect_input() {
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
    this->current_speed = PLAYER_RUN_SPEED;
  }
  else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
    this->current_speed = -PLAYER_RUN_SPEED;
  }
  else {
    this->current_speed = 0;
  }

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
    this->current_turn_speed = -PLAYER_TURN_SPEED;
  }
  else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
    this->current_turn_speed = PLAYER_TURN_SPEED;
  }
  else {
    this->current_turn_speed = 0;
  }

  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
    this->jump();
  }
}
