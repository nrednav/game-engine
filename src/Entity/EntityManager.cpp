#include "EntityManager.h"
#include "Loader/OBJLoader.h"
#include "Utils/RNG.h"

#include <iostream>

EntityManager* EntityManager::instance = nullptr;

EntityManager* EntityManager::getInstance()
{
	return instance = (instance != nullptr)
		? instance : new EntityManager();
}

void EntityManager::initialize(Loader* loader, Terrain* initialTerrain)
{
	this->loader = loader;
	this->activeTerrain = initialTerrain;
	this->loadEntityModels();
}

void EntityManager::generateEntities(int count)
{
	this->createLights();

	for (int i = 0; i < count; i++) {
		if (i % 10 == 0) {
			this->createEntity("grass", 0.9f);
			this->createEntity("flower", 2.3f);
			this->createEntity("fern", 0.9f);
		}

		if (i % 5 == 0) {
			float treeScale = RNG::randomFloat() * 4 + 1;
			this->createEntity("pine", treeScale);
			this->createEntity("lowPolyTree", treeScale);
		}
	}
}

void EntityManager::loadEntityModels()
{
	// Objects
	this->models["player"] = this->createModel("player", loader);
	this->models["lamp"] = this->createModel("lamp", loader, false, true);

	// Environment
	this->models["pine"] = this->createModel("pine", loader);
	this->models["lowPolyTree"] = this->createModel("lowPolyTree", loader);
	this->models["grass"] = this->createModel("grass", loader, true, true);
	this->models["flower"] = this->createModel("flower", loader, true, true);
	this->models["fern"] = this->createModel("fern", loader, true, false, true, 2);
}

void EntityManager::recalculateEntityPositions(Terrain* currentTerrain)
{
	for (unsigned int i = 0; i < this->entities.size(); i++) {
		float x = this->entities[i]->getPosition().x;
		float z = this->entities[i]->getPosition().z;
		float y = currentTerrain->getTerrainHeightAt(x, z);
		this->entities[i]->setPosition(glm::vec3(x, y, z));
	}
}

Player* EntityManager::createPlayer(std::string name, float scaleFactor)
{
	glm::vec3 position;
	position.x = RNG::randomFloat() * 800 - 400;
	position.z = RNG::randomFloat() * -600;
	position.y = this->activeTerrain->getTerrainHeightAt(position.x, position.z);
	
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(scaleFactor, scaleFactor, scaleFactor);

	return new Player(this->models[name], position, rotation, scale);
}


/* Private helper methods */
void EntityManager::createEntity(
	std::string name, float scaleFactor, bool duplicate
) {
	TexturedModel* model = this->models[name];

	glm::vec3 position;
	position.x = RNG::randomFloat() * 800 - 400;
	position.z = RNG::randomFloat() * -600;
	position.y = this->activeTerrain->getTerrainHeightAt(position.x, position.z);

	glm::vec3 rotation = glm::vec3(0, RNG::randomFloat() * 360, 0);
	glm::vec3 scale = glm::vec3(scaleFactor, scaleFactor, scaleFactor);

	if (model->getTexture()->getNumberOfRows() > 1)
		this->entities.push_back(new Entity(model, position, rotation, scale, RNG::randomInt(4)));
	else
		this->entities.push_back(new Entity(model, position, rotation, scale));

	if (duplicate) {
		Entity* lastEntity = this->entities[this->entities.size() - 1];

		float x = -(lastEntity->getPosition().x);
		float z = -(lastEntity->getPosition().z);
		float y = this->activeTerrain->getTerrainHeightAt(x, z);

		Entity* duplicate = new Entity(
			lastEntity->getModel(),
			glm::vec3(x, y, z),
			lastEntity->getRotation(),
			lastEntity->getScale()
		);

		this->entities.push_back(duplicate);
	}
}

TexturedModel* EntityManager::createModel(
	std::string name,
	Loader* loader,
	bool hasTransparency,
	bool usesFakeLighting,
	bool usesTextureAtlas,
	int numOfRowsInAtlas
) {
	RawModel* entityRawModel = OBJLoader::loadModel_v2(name, loader);

	ModelTexture* entityTexture = new ModelTexture(loader->loadTexture(name));
	if (usesTextureAtlas)
		entityTexture->setNumberOfRows(numOfRowsInAtlas);

	TexturedModel* entityTexturedModel = new TexturedModel(entityRawModel, entityTexture);

	if (hasTransparency)
		entityTexturedModel->getTexture()->setTransparency(true);

	if (usesFakeLighting)
		entityTexturedModel->getTexture()->useFakeLighting(true);

	return entityTexturedModel;
}

void EntityManager::createLights()
{
	Light* sun = new Light(glm::vec3(0, 1000, 0), glm::vec3(1, 1, 1));
	this->createEntity("lamp", 1.0f, false);
	Entity* lamp = this->entities[this->entities.size() - 1];

	glm::vec3 position = lamp->getPosition();
	position.y += 12.0f;

	glm::vec3 color = glm::vec3(2, 2, 0);
	glm::vec3 attenuation = glm::vec3(1, 0.01f, 0.002f);

	this->lights.push_back(sun);
	this->lights.push_back(new Light(position, color, attenuation));
}

void EntityManager::cleanup()
{
	this->loader = nullptr;
	this->activeTerrain = nullptr;
	this->entities.clear();
	this->models.clear();
}
