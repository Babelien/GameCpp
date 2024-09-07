#pragma once

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts, 
		const unsigned int* indices, unsigned int numIndices, const float* texCoord);
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void setActive();

	unsigned int getNumIndices() const { return mNumIndices; }
	unsigned int getNumVerts() const { return mNumVerts; }

private:
	unsigned int mNumIndices;
	unsigned int mNumVerts;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
	unsigned int mVertexBuffer;
	unsigned int mTexCoordBuffer;
};
