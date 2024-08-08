#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Terrain/Terrain.h"

class Player : public Entity {
public:
  Player(TexturedModel* model, glm::vec3 position, glm::vec3 rotation,
         glm::vec3 scale);
  void move(Terrain* terrain);
  void jump();

private:
  float current_speed = 0;
  float current_turn_speed = 0;
  float vertical_speed = 0;
  bool is_airborne = false;

  void detect_input();
};

#endif // !PLAYER_H
