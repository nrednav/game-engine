#include "GL/glew.h"
#include "SkyboxRenderer.h"
#include "Display/DisplayManager.h"

#include "glm/gtc/constants.hpp"

SkyboxRenderer::SkyboxRenderer(SkyboxShader* shader, Loader* loader,
                               glm::mat4 projectionMatrix) {
  this->cube = loader->loadToVAO(this->vertices, 3);
  this->dayTextureID = loader->loadCubeMap(this->dayTextureFiles);
  this->nightTextureID = loader->loadCubeMap(this->nightTextureFiles);
  this->shader = shader;

  this->shader->start();
  this->shader->connectTextureUnits();
  this->shader->loadProjectionMatrix(projectionMatrix);
  this->shader->stop();
}

void SkyboxRenderer::render(Camera* camera, glm::vec3 color) {
  this->shader->start();
  this->shader->loadViewMatrix(camera);
  this->shader->loadFogColor(color);

  glBindVertexArray(this->cube->getVaoID());
  glEnableVertexAttribArray(0);

  this->bindTextures();
  glDrawArrays(GL_TRIANGLES, 0, this->cube->getVertexCount());

  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
  this->shader->stop();
}

void SkyboxRenderer::bindTextures() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->dayTextureID);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->nightTextureID);

  this->shader->loadBlendFactor(this->getBlendFactor());
}

float SkyboxRenderer::getBlendFactor() {
  this->time += (float)DisplayManager::getInstance()->getFrameTimeSeconds();
  float delta = -1 * this->time * 2 * glm::pi<float>() / SKYBOX_CYCLE_LENGTH;

  return (float)glm::abs(0.5f * glm::cos(glm::radians(delta)) - 0.5f);
}
