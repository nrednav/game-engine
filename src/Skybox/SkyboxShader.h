#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "Shader/ShaderProgram.h"
#include "Entity/Camera.h"

class SkyboxShader : public ShaderProgram {
public:
  SkyboxShader(std::string vertexFile, std::string fragmentFile);
  void loadProjectionMatrix(glm::mat4 matrix);
  void loadViewMatrix(Camera* camera);
  void loadFogColor(glm::vec3 color);
  void loadBlendFactor(float value);
  void connectTextureUnits();

public:
  void bindAttributes();
  void getAllUniformLocations();

private:
  int location_projectionMatrix;
  int location_viewMatrix;
  int location_fogColor;
  int location_cubeMapDay;
  int location_cubeMapNight;
  int location_blendFactor;

  float currentRotation = 0.0f;
};

#endif // !SKYBOXSHADER_H
