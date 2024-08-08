#define GLM_ENABLE_EXPERIMENTAL

#include "SkyboxShader.h"
#include "Constants.h"
#include "Display/DisplayManager.h"
#include "Utils/Math.h"
#include "glm/gtx/transform.hpp"

SkyboxShader::SkyboxShader(std::string vertexFile, std::string fragmentFile)
    : ShaderProgram(vertexFile, fragmentFile) {
  this->bindAttributes();
  this->getAllUniformLocations();
}

void SkyboxShader::bindAttributes() { bindAttribute(0, "position"); }

void SkyboxShader::getAllUniformLocations() {
  this->location_projectionMatrix = getUniformLocation("projectionMatrix");
  this->location_viewMatrix = getUniformLocation("viewMatrix");
  this->location_fogColor = getUniformLocation("fogColor");
  this->location_cubeMapDay = getUniformLocation("cubeMapDay");
  this->location_cubeMapNight = getUniformLocation("cubeMapNight");
  this->location_blendFactor = getUniformLocation("blendFactor");
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix) {
  loadMatrix(this->location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(Camera* camera) {
  glm::mat4 viewMatrix = Math::createViewMatrix(camera);

  viewMatrix[3][0] = 0;
  viewMatrix[3][1] = 0;
  viewMatrix[3][2] = 0;

  this->currentRotation +=
      SKYBOX_ROTATION_SPEED *
      (float)DisplayManager::getInstance()->getFrameTimeSeconds();

  viewMatrix = glm::rotate(viewMatrix, glm::radians(this->currentRotation),
                           glm::vec3(0, 1, 0));

  loadMatrix(this->location_viewMatrix, viewMatrix);
}

void SkyboxShader::loadFogColor(glm::vec3 color) {
  loadVector(this->location_fogColor, color);
}

void SkyboxShader::loadBlendFactor(float value) {
  loadFloat(this->location_blendFactor, value);
}

void SkyboxShader::connectTextureUnits() {
  loadInt(this->location_cubeMapDay, 0);
  loadInt(this->location_cubeMapNight, 1);
}
