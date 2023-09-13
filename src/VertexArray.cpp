#include "VertexArray.h"
#include "glew.h"
VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
{
	// generate vertex array and store in mVertexArray
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// create a vertex buffer GL_ARRAY_BUFFER is command
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	glBufferData(
		GL_ARRAY_BUFFER,	// the active buffer type to write to
		numVerts * 3 * sizeof(float),	// number of bytes to copy
		verts,	// sources to copy from (pointer)
		GL_STATIC_DRAW // load data once
	);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,	// index buffer
		numIndices * sizeof(unsigned int),	// size of data
		indices,
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(0); // enable first vertex attribute (position)

	glVertexAttribPointer(
		0,	// attribute index (0 for first one)
		3, // number of component (x,y,z)
		GL_FLOAT,	// type of components
		GL_FALSE,	// only used for integral types
		sizeof(float) *3,	// stride (usually size of each vertex)
		0	// offset from start of vertex to this attribute
	);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive() 
{
	glBindVertexArray(mVertexArray);
}
