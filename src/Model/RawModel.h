#ifndef RAWMODEL_H
#define RAWMODEL_H

class RawModel {
public:
	RawModel(unsigned int vaoID, unsigned int vertexCount);
	unsigned int getVaoID() const { return this->vaoID; }
	unsigned int getVertexCount() const { return this->vertexCount; }
private:
	unsigned int vaoID;
	unsigned int vertexCount;
};

#endif // !RAWMODEL_H
