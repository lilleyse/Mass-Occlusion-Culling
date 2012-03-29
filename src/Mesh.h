#pragma once
#include <gl3w/gl3w.h>

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


class Mesh
{
public:
	Mesh(float* positionData, int numVertices, unsigned short* elementArray, int numTriangles);
	~Mesh();

	void render();

private:

	int numTriangles;
	GLuint vertexArrayObject;
	GLuint arrayBufferObject;
	GLuint elementBufferObject;


};