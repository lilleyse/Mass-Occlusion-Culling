#pragma once

#include <glew/glew.h>
#include <glew/wglew.h>
#include <vector>
#include <iostream>
#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


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
	int numInstances;

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
	POSITION,
	TRANSFORM
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
	GLuint transformsBufferObject;
	GLuint elementBufferObject;
	GLuint indirectBufferObject;
	GLuint instanceAtomicCounter;

};
