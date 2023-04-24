#include "Player.h"
#include "GLFW/glfw3.h"
#include "Display/DisplayManager.h"
#include "Constants.h"

#include <iostream>
#include "math.h"

Player::Player(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
: Entity(model, position, rotation, scale) {}

void Player::move(Terrain* terrain)
{
	this->detectInput();

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		this->currentSpeed *= 5;
	}

	float frameTimeSeconds = (float)DisplayManager::getInstance()->getFrameTimeSeconds();

	glm::vec3 lastSafePos = this->getPosition();

	// Horizontal Movement
	this->changeRotation(glm::vec3(0, this->currentTurnSpeed * frameTimeSeconds, 0));
	float distance = this->currentSpeed * frameTimeSeconds;
	float dx = distance * glm::sin(glm::radians(this->getRotation().y));
	float dz = distance * glm::cos(glm::radians(this->getRotation().y));

	bool xOutOfBounds = dx + this->getPosition().x >= TERRAIN_SIZE
		|| dx + this->getPosition().x <= -TERRAIN_SIZE;
	bool zOutOfBounds = dz + this->getPosition().z >= TERRAIN_SIZE
		|| dz + this->getPosition().z <= -TERRAIN_SIZE;

	if (xOutOfBounds || zOutOfBounds)
		this->setPosition(lastSafePos);
	else
		this->changePosition(glm::vec3(dx, 0, dz));

	// Vertical Movement (E.g. jump)
	this->verticalSpeed += PLAYER_GRAVITY * frameTimeSeconds;
	this->changePosition(
		glm::vec3(0, this->verticalSpeed * frameTimeSeconds, 0)
	);

	float terrainHeight = terrain->getTerrainHeightAt(
		this->getPosition().x,
		this->getPosition().z
	);

	if (this->getPosition().y < terrainHeight) {
		this->verticalSpeed = 0;
		this->isAirborne = false;
		this->setPosition(
			glm::vec3(this->getPosition().x, terrainHeight, this->getPosition().z)
		);
	}
}

void Player::jump() { 
	if (!this->isAirborne) {
		this->verticalSpeed = JUMP_FORCE;
		this->isAirborne = true;
	}
}

void Player::detectInput()
{
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
