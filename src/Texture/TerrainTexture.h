#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H

class TerrainTexture {
public:
	TerrainTexture(unsigned int textureID)
		: textureID(textureID) {}

	unsigned int getTextureID() const { return this->textureID; }

private:
	unsigned int textureID;
};

#endif // !TERRAINTEXTURE_H
