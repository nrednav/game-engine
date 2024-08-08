#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"

#include <vector>

class StaticShader : public ShaderProgram {
public:
  StaticShader(std::string vertexFile, std::string fragmentFile);
  void loadTransformationMatrix(glm::mat4 matrix);
  void loadProjectionMatrix(glm::mat4 matrix);
  void loadViewMatrix(Camera* camera);
  void loadLights(std::vector<Light*> lights);
  void loadSpecularLightingVariables(float shineDamper, float reflectivity);
  void loadFakeLightingVariable(bool value);
  void loadSkyColor(glm::vec3 rgb);
  void loadNumOfRowsInTexture(int numOfRows);
  void loadTextureOffset(float x, float y);

public:
  void bindAttributes();
  void getAllUniformLocations();

private:
  const int MAX_LIGHT_COUNT = 21;
  std::vector<int> location_lightPositions;
  std::vector<int> location_lightColors;
  std::vector<int> location_lightAttenuations;

  int location_transformationMatrix;
  int location_projectionMatrix;
  int location_viewMatrix;
  int location_shineDamper;
  int location_reflectivity;
  int location_useFakeLighting;
  int location_skyColor;
  int location_numOfRowsInTexture;
  int location_textureOffset;
};

#endif // !STATICSHADER_H
