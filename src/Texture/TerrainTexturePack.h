#ifndef TERRAINTEXTUREPACK_H
#define TERRAINTEXTUREPACK_H

#include "TerrainTexture.h"

class TerrainTexturePack {
public:
	TerrainTexturePack(
		TerrainTexture* bgTexture,
		TerrainTexture* rTexture,
		TerrainTexture* gTexture,
		TerrainTexture* bTexture
	) {
		this->bgTexture = bgTexture;
		this->rTexture = rTexture;
		this->gTexture = gTexture;
		this->bTexture = bTexture;
	}

	TerrainTexture* getBackgroundTexture() const { return this->bgTexture; }
	TerrainTexture* getRedTexture() const { return this->rTexture; }
	TerrainTexture* getGreenTexture() const { return this->gTexture; }
	TerrainTexture* getBlueTexture() const { return this->bTexture; }

private:
	TerrainTexture* bgTexture;
	TerrainTexture* rTexture;
	TerrainTexture* gTexture;
	TerrainTexture* bTexture;
};

#endif // !TERRAINTEXTUREPACK_H
