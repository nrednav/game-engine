#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"
#include "Texture/ModelTexture.h"

class TexturedModel {
public:
  TexturedModel(RawModel* model, ModelTexture* texture)
      : rawModel(model), texture(texture) {}

  RawModel* getRawModel() const { return this->rawModel; }
  ModelTexture* getTexture() const { return this->texture; }

private:
  RawModel* rawModel;
  ModelTexture* texture;
};

#endif // !TEXTUREMODEL_H
