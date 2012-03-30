#pragma once

#include <glew/glew.h>
#include <glew/wglew.h>
#include <vector>
#include <iostream>


struct DrawElementsIndirectCommand
{
	GLuint count;
	GLuint primCount;
	GLuint firstIndex;
	GLint  baseVertex;
	GLuint baseInstance;
};

struct Mesh
{
	float* positionData;
	unsigned short* elementArray;
	int numVertices;
	int numElements;

	DrawElementsIndirectCommand indirectCommand;
};

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
	float s, t;
};

enum Attributes
{
	POSITION
};




class MeshLibrary
{
public:

	MeshLibrary();
	~MeshLibrary();

	void initialize();
	void render();

private:

	GLuint vertexArrayObject;
	GLuint arrayBufferObject;
	GLuint elementBufferObject;
	GLuint indirectBufferObject;

};
