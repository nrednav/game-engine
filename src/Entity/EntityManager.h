#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Loader/Loader.h"
#include "Terrain/Terrain.h"
#include "Entity/Entity.h"
#include "Entity/Light.h"
#include "Entity/Player.h"

#include <vector>
#include <map>
#include <string>

class EntityManager {
public:
	static EntityManager* getInstance();
	void initialize(Loader* loader, Terrain* initialTerrain);

	Player* createPlayer(std::string name, float scaleFactor);

	void generateEntities(int count);
	void loadEntityModels();
	void recalculateEntityPositions(Terrain* currentTerrain);
	void cleanup();

	// Getters
	std::vector<Entity*> getEntities() const { return this->entities; }
	std::vector<Light*> getLights() const { return this->lights; }

private:
	EntityManager() {}

	static EntityManager* instance;

	Loader* loader;
	Terrain* activeTerrain;
	std::vector<Entity*> entities;
	std::map<std::string, TexturedModel*> models;
	std::vector<Light*> lights;

	void createEntity(std::string name, float scale, bool duplicate = true);
	TexturedModel* createModel(
		std::string name,
		Loader* loader,
		bool hasTransparency = false,
		bool usesFakeLighting = false,
		bool usesTextureAtlas = false,
		int numOfRowsInAtlas = 1
	);
	void createLights();
};

#endif // !ENTITYMANAGER_H
