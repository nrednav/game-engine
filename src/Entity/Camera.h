#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"

class Camera {
public:
  Camera(Player* player, glm::vec3 position);

  glm::vec3 get_position() const { return this->position; }
  float get_pitch() const { return this->pitch; }
  float get_yaw() const { return this->yaw; }
  float get_roll() const { return this->roll; }

  void move();

private:
  glm::vec3 position = glm::vec3(0, 0, 0);

  float pitch = 15.0f;
  float yaw = 0.0f;
  float roll = 0.0f;

  float distance_from_player = 30.0f;
  float angle_around_player = 0.0f;

  float last_zoom_level;
  float zoom_level;

  Player* player;

  void calculate_zoom();
  void calculate_pitch();
  void calculate_angle_around_player();

  float calculate_horizontal_distance();
  float calculate_vertical_distance();
  void calculate_camera_position(
    const float& horizontal_distance,
    const float& vertical_distance
  );
};

#endif // !CAMERA_H
