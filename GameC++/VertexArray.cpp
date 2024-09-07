#include "VertexArray.h"
#include <GLEW/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts, 
	const unsigned int* indices, unsigned int numIndices, const float* texCoord)
	:mNumVerts(numVerts)
	,mNumIndices(numIndices)
{
	// VAO
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
	// VBO
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(float), verts, GL_STATIC_DRAW);
	// TextureCoord
	glGenBuffers(1, &mTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, 2 * numVerts * sizeof(float), texCoord, GL_STATIC_DRAW);
	// IBO
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
}

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// VAO
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
	// VBO
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 5 * numVerts * sizeof(float), verts, GL_STATIC_DRAW);
	// IBO
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mTexCoordBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::setActive()
{
	glBindVertexArray(mVertexArray);
}