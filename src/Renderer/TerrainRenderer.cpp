#include "GL/glew.h"
#include "TerrainRenderer.h"
#include "Utils/Math.h"

TerrainRenderer::TerrainRenderer(TerrainShader* shader,
                                 glm::mat4& projectionMatrix) {
  this->shader = shader;
  this->shader->start();
  this->shader->loadProjectionMatrix(projectionMatrix);
  this->shader->connectTextureUnits();
  this->shader->stop();
}

void TerrainRenderer::render(std::vector<Terrain*>& terrains) {
  for (Terrain* terrain : terrains) {
    prepareTerrain(terrain);
    loadModelMatrix(terrain);
    glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(),
                   GL_UNSIGNED_INT, 0);
    unbindTerrainModel();
  }
}

void TerrainRenderer::prepareTerrain(Terrain* terrain) {
  RawModel* rawModel = terrain->getModel();
  glBindVertexArray(rawModel->getVaoID());

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  this->bindTextures(terrain);
  this->shader->loadSpecularLightingVariables(
      1, 0); // TO-DO: Add shine variables to terrain
}

void TerrainRenderer::bindTextures(Terrain* terrain) {
  TerrainTexturePack* texturePack = terrain->getTexturePack();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,
                texturePack->getBackgroundTexture()->getTextureID());

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texturePack->getRedTexture()->getTextureID());

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, texturePack->getGreenTexture()->getTextureID());

  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, texturePack->getBlueTexture()->getTextureID());

  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap()->getTextureID());
}

void TerrainRenderer::unbindTerrainModel() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain* terrain) {
  glm::mat4 transformationMatrix = Math::createTransformationMatrix(
      glm::vec3(terrain->getX(), 0, terrain->getZ()), glm::vec3(0, 0, 0),
      glm::vec3(1, 1, 1));
  this->shader->loadTransformationMatrix(transformationMatrix);
}
