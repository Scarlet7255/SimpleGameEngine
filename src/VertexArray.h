#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void Active();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	// OpenGL ID of vertex buffer
	unsigned int mVertexBuffer;
	// OpenGL ID of index buffer
	unsigned int mIndexBuffer;
	// OpenGL ID of vertex array object
	unsigned int mVertexArray;
};


#endif // !VERTEXARRAY_H
