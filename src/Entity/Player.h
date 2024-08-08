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
  float currentSpeed = 0;
  float currentTurnSpeed = 0;
  float verticalSpeed = 0;
  bool isAirborne = false;

  void detectInput();
};

#endif // !PLAYER_H
