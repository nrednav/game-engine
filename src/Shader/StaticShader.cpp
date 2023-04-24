#include "StaticShader.h"
#include "Utils/Math.h"

StaticShader::StaticShader(std::string vertexFile, std::string fragmentFile)
	: ShaderProgram(vertexFile, fragmentFile)
{
	this->bindAttributes();
	this->getAllUniformLocations();
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations()
{
	this->location_transformationMatrix = getUniformLocation("transformationMatrix");
	this->location_projectionMatrix = getUniformLocation("projectionMatrix");
	this->location_viewMatrix = getUniformLocation("viewMatrix");
	this->location_shineDamper = getUniformLocation("shineDamper");
	this->location_reflectivity = getUniformLocation("reflectivity");
	this->location_useFakeLighting = getUniformLocation("useFakeLighting");
	this->location_skyColor = getUniformLocation("skyColor");
	this->location_numOfRowsInTexture = getUniformLocation("numOfRowsInTexture");
	this->location_textureOffset = getUniformLocation("textureOffset");

	this->location_lightPositions = std::vector<int>(MAX_LIGHT_COUNT);
	this->location_lightColors = std::vector<int>(MAX_LIGHT_COUNT);
	this->location_lightAttenuations = std::vector<int>(MAX_LIGHT_COUNT);
	for (int i = 0; i < MAX_LIGHT_COUNT; i++) {
		this->location_lightPositions[i] = getUniformLocation(
			"lightPosition[" + std::to_string(i) + "]"
		);
		this->location_lightColors[i] = getUniformLocation(
			"lightColor[" + std::to_string(i) + "]"
		);
		this->location_lightAttenuations[i] = getUniformLocation(
			"lightAttenuation[" + std::to_string(i) + "]"
		);
	}
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(this->location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix(this->location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera* camera)
{
	glm::mat4 viewMatrix = Math::createViewMatrix(camera);
	loadMatrix(this->location_viewMatrix, viewMatrix);
}

void StaticShader::loadLights(std::vector<Light*> lights)
{
	for (int i = 0; i < MAX_LIGHT_COUNT; i++) {
		if (i < lights.size()) {
			loadVector(location_lightPositions[i], lights[i]->getPosition());
			loadVector(location_lightColors[i], lights[i]->getColor());
			loadVector(location_lightAttenuations[i], lights[i]->getAttenuation());
		}
		else {
			loadVector(location_lightPositions[i], glm::vec3(0, 0, 0));
			loadVector(location_lightColors[i], glm::vec3(0, 0, 0));
			loadVector(location_lightAttenuations[i], glm::vec3(1, 0, 0));
		}
	}
}

void StaticShader::loadSpecularLightingVariables(float shineDamper, float reflectivity)
{
	loadFloat(this->location_shineDamper, shineDamper);
	loadFloat(this->location_reflectivity, reflectivity);
}

void StaticShader::loadFakeLightingVariable(bool value)
{
	loadBool(this->location_useFakeLighting, value);
}

void StaticShader::loadSkyColor(glm::vec3 rgb)
{
	loadVector(this->location_skyColor, rgb);
}

void StaticShader::loadNumOfRowsInTexture(int numOfRows)
{
	loadFloat(location_numOfRowsInTexture, (float) numOfRows);
}

void StaticShader::loadTextureOffset(float x, float y)
{
	loadVector2D(location_textureOffset, glm::vec2(x, y));
}
