#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"

#include <vector>

class TerrainShader : public ShaderProgram {
public:
	TerrainShader(std::string vertexFile, std::string fragmentFile);
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera* camera);
	void loadLights(std::vector<Light*> lights);
	void loadSpecularLightingVariables(float shineDamper, float reflectivity);
	void loadSkyColor(glm::vec3 rgb);
	void connectTextureUnits();

public:
	void bindAttributes();
	void getAllUniformLocations();

private:
	const int MAX_LIGHT_COUNT = 4;
	std::vector<int> location_lightPositions;
	std::vector<int> location_lightColors;
	std::vector<int> location_lightAttenuations;

	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;

	int location_shineDamper;
	int location_reflectivity;
	int location_skyColor;

	int location_bgTexture;
	int location_rTexture;
	int location_gTexture;
	int location_bTexture;
	int location_blendMap;
};

#endif // !TERRAINSHADER_H
