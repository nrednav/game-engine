#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "stb_image.h"

class TextureData {
public:
	TextureData(stbi_uc* imageData, int width, int height)
		: buffer(imageData), width(width), height(height) {}

	int getWidth() const { return this->width; }
	int getHeight() const { return this->height; }
	stbi_uc* getBuffer() const { return this->buffer; }

private:
	int width;
	int height;
	stbi_uc* buffer;
};

#endif // !TEXTUREDATA_H
