#include "Terrain.h"
#include "Utils/Math.h"
#include "Constants.h"

#include <vector>
#include <iostream>

Terrain::Terrain(
	float gridX, float gridZ, Loader* loader,
	TerrainTexturePack* texturePack,
	TerrainTexture* blendMap,
	std::string heightMapFilename
) {
	this->texturePack = texturePack;
	this->blendMap = blendMap;
	this->x = gridX * TERRAIN_SIZE;
	this->z = gridZ * TERRAIN_SIZE;
	this->model = generateTerrain(loader, heightMapFilename);
}

RawModel* Terrain::generateTerrain(Loader* loader, std::string heightMapFilename)
{
	int imageWidth, imageHeight, nComponents;
	std::string hmPath = "assets/textures/" + heightMapFilename + ".png";
	stbi_uc* imageData = stbi_load(hmPath.c_str(), &imageWidth, &imageHeight, &nComponents, STBI_rgb);

	int TERRAIN_VERTEX_COUNT = imageWidth;

	this->heightMap = std::vector<std::vector<float>>(
		TERRAIN_VERTEX_COUNT, std::vector<float>(TERRAIN_VERTEX_COUNT, 0.0f)
	);

	int tileCount = TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT;
	int lastTerrainIndex = TERRAIN_VERTEX_COUNT - 1;

	std::vector<float> vertices(tileCount * 3);
	std::vector<float> normals(tileCount * 3);
	std::vector<float> textureCoords(tileCount * 2);
	std::vector<int> indices(6 * lastTerrainIndex * lastTerrainIndex);

	unsigned int vertexPointer = 0;

	for (int i = 0; i < TERRAIN_VERTEX_COUNT; i++) {
		for (int j = 0; j < TERRAIN_VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = -(float)j / ((float)lastTerrainIndex) * TERRAIN_SIZE;
			float height = this->getHeight(j, i, imageData, imageWidth);
			this->heightMap[j][i] = height;
			vertices[vertexPointer * 3 + 1] = height;
			vertices[vertexPointer * 3 + 2] = -(float)i / ((float)lastTerrainIndex) * TERRAIN_SIZE;

			glm::vec3 normal = this->calculateNormal(j, i, imageData, imageWidth);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;

			textureCoords[vertexPointer * 2] = (float)j / ((float)lastTerrainIndex);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)lastTerrainIndex);

			vertexPointer++;
		}
	}

	unsigned int pointer = 0;
	for (int gridZ = 0; gridZ < lastTerrainIndex; gridZ++) {
		for (int gridX = 0; gridX < lastTerrainIndex; gridX++) {
			int topLeft = (gridZ * TERRAIN_VERTEX_COUNT) + gridX;
			int topRight = topLeft + 1;
			int bottomLeft = ((gridZ + 1) * TERRAIN_VERTEX_COUNT) + gridX;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	return loader->loadToVAO(vertices, indices, textureCoords, normals);
}

float Terrain::getHeight(const int& x, const int& z, stbi_uc* imageData, const int& imageWidth)
{
	if (x < 0 || x >= imageWidth || z < 0 || z >= imageWidth) {
		return 1.0f;
	}

	const stbi_uc* pixel = imageData + (3 * (z * imageWidth + x));
	int height = pixel[0];
	int input_range = 255 - 0;
	int output_range = (int) (TERRAIN_MAX_HEIGHT - TERRAIN_MIN_HEIGHT);

	float output = (height - 0) * output_range / input_range + TERRAIN_MIN_HEIGHT;

	return output;
}

glm::vec3 Terrain::calculateNormal(const int& x, const int& z, stbi_uc* imageData, const int& imageWidth)
{
	float heightL = this->getHeight(x - 1, z, imageData, imageWidth);
	float heightR = this->getHeight(x + 1, z, imageData, imageWidth);
	float heightU = this->getHeight(x, z + 1, imageData, imageWidth);
	float heightD = this->getHeight(x, z - 1, imageData, imageWidth);
	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
	return glm::normalize(normal);
}

float Terrain::getTerrainHeightAt(float worldX, float worldZ)
{
	float terrainX = worldX - this->x;
	float terrainZ = worldZ - this->z;
	float gridTileSize = -(TERRAIN_SIZE / ((float)this->heightMap.size() - 1));

	int gridX = (int) glm::floor(terrainX / gridTileSize);
	int gridZ = (int) glm::floor(terrainZ / gridTileSize);

	bool xOutOfBounds = gridX >= this->heightMap.size() - 1 || gridX < 0;
	bool zOutOfBounds = gridZ >= this->heightMap.size() - 1 || gridZ < 0;
	if (xOutOfBounds || zOutOfBounds)
		return 0.0f;

	float xCoord = fmod(terrainX, gridTileSize) / gridTileSize;
	float zCoord = fmod(terrainZ, gridTileSize) / gridTileSize;

	float terrainHeight;
	if (xCoord <= (1 - zCoord)) {
		terrainHeight = Math::getBarryCentricCoordinate(
			glm::vec3(0, this->heightMap[gridX][gridZ], 0),
			glm::vec3(1, this->heightMap[gridX + 1][gridZ], 0),
			glm::vec3(0, this->heightMap[gridX][gridZ + 1], 1),
			glm::vec2(xCoord, zCoord)
		);
	}
	else {
		terrainHeight = Math::getBarryCentricCoordinate(
			glm::vec3(1, this->heightMap[gridX + 1][gridZ], 0),
			glm::vec3(1, this->heightMap[gridX + 1][gridZ + 1], 1),
			glm::vec3(0, this->heightMap[gridX][gridZ + 1], 1),
			glm::vec2(xCoord, zCoord)
		);
	}

	return terrainHeight;
}
