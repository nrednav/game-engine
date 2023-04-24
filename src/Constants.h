#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Display */
const unsigned int DISPLAY_WIDTH = 1280;
const unsigned int DISPLAY_HEIGHT = 720;

/* Renderer */
const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1600.0f;
const float SKY_COLOR_R = 0.5f;
const float SKY_COLOR_G = 0.5f;
const float SKY_COLOR_B = 0.5f;

/* Entity */
const int ENTITY_COUNT = 200;

/* Camera */
const float CAMERA_SPEED = 0.1f;
const float CAMERA_ZOOM_LEVEL = 1.0f;

/* Terrain */
const float TERRAIN_SIZE = 800;
const int TERRAIN_VERTEX_COUNT = 128;
const float TERRAIN_HEIGHT = 0;
const float TERRAIN_MAX_HEIGHT = 40;
const float TERRAIN_MIN_HEIGHT = -40;
const float TERRAIN_MAX_PIXEL_COLOR = 256 * 256 * 256;

/* Player */
const float PLAYER_RUN_SPEED = 15.0f;
const float PLAYER_TURN_SPEED = 180.0f;
const float PLAYER_GRAVITY = -50.0f;
const float JUMP_FORCE = 30.0f;

/* Skybox */
const float SKYBOX_SIZE = 500.0f;
const float SKYBOX_ROTATION_SPEED = 2.0f;
const float SKYBOX_CYCLE_LENGTH = 4;

#endif // !CONSTANTS_H
