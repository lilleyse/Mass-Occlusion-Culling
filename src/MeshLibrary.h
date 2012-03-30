#pragma once

#include <gl3w/gl3w.h>
#include <vector>



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

struct DrawElementsIndirectData
{
	GLuint count;
	GLuint primCount;
	GLuint firstIndex;
	GLint  baseVertex;
	GLuint baseInstance;
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
