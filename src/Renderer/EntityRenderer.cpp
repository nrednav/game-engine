#include "GL/glew.h"
#include "MasterRenderer.h"
#include "EntityRenderer.h"
#include "Utils/Math.h"

#include <iostream>

EntityRenderer::EntityRenderer(StaticShader* shader, glm::mat4& projectionMatrix)
{
	this->shader = shader;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void EntityRenderer::render(std::map<TexturedModel*, std::vector<Entity*>>& entities)
{
	std::map<TexturedModel*, std::vector<Entity*>>::iterator it = entities.begin();

	while (it != entities.end()) {
		prepareTexturedModel(it->first);
		std::vector<Entity*> batch = it->second;

		for (Entity* entity : batch) {
			prepareEntity(entity);
			glDrawElements(
				GL_TRIANGLES, 
				it->first->getRawModel()->getVertexCount(), 
				GL_UNSIGNED_INT, 0
			);
		}

		unbindTexturedModel();
		it++;
	}
}

void EntityRenderer::prepareTexturedModel(TexturedModel* model)
{
	RawModel* rawModel = model->getRawModel();
	glBindVertexArray(rawModel->getVaoID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture* texture = model->getTexture();
	this->shader->loadNumOfRowsInTexture(texture->getNumberOfRows());

	if (texture->hasTransparency())
		MasterRenderer::disableCulling();

	this->shader->loadFakeLightingVariable(texture->usesFakeLighting());
	this->shader->loadSpecularLightingVariables(
		texture->getShineDamper(),
		texture->getReflectivity()
	);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void EntityRenderer::unbindTexturedModel()
{
	MasterRenderer::enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareEntity(Entity* entity)
{
	glm::mat4 transformationMatrix = Math::createTransformationMatrix(
		entity->getPosition(), 
		entity->getRotation(), 
		entity->getScale()
	);
	this->shader->loadTransformationMatrix(transformationMatrix);
	this->shader->loadTextureOffset(
		entity->getTextureXOffset(),
		entity->getTextureYOffset()
	);
}
