#include "MeshLibrary.h"

MeshLibrary::MeshLibrary()
{

}

MeshLibrary::~MeshLibrary()
{

}

void MeshLibrary::initialize()
{

	//create mesh0

	int numVertices = 24;
	int numElements = 36;

	float positionData[] =
    {
		1, 1, -1,
		1, -1, -1,
		-1, -1, -1,
		-1, 1, -1,
		1, 1, 1,
		-1, 1, 1,
		-1, -1, 1,
		1, -1, 1,
		1, 1, -1,
		1, 1, 1,
		1, -1, 1, 
		1, -1, -1, 
		1, -1, -1,
		1, -1, 1,
		-1, -1, 1,
		-1, -1, -1,
		-1, -1, -1,
		-1, -1, 1,
		-1, 1, 1,
		-1, 1, -1,
		1, 1, 1,
		1, 1, -1,
		-1, 1, -1,
		-1, 1, 1,
	};

	unsigned short elementArray[] =
    {
       0, 1, 2, 
	   0, 2, 3, 
	   4, 5, 6, 
	   4, 6, 7, 
	   8, 9, 10, 
	   8, 10, 11, 
	   12, 13, 14, 
	   12, 14, 15,
	   16, 17, 18, 
	   16, 18, 19, 
	   20, 21, 22, 
	   20, 22, 23,
    };


	//create opengl mesh based on the positions
	Vertex* vertices = new Vertex[numVertices];

	for(int i = 0; i < numVertices; i++)
	{
		vertices[i].x = positionData[i*3 + 0];
		vertices[i].y = positionData[i*3 + 1];
		vertices[i].z = positionData[i*3 + 2];
	}

	//create and bind array buffer, set data
    glGenBuffers(1, &arrayBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*numVertices, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //create and bind element array buffer, set data to the stored element array, then close buffer
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*numElements, elementArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create and bind vao
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //bind array buffer again
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);

	//enable vertex attributes
	glEnableVertexAttribArray(GLuint(POSITION));

	//set position attrib pointer
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//bind element array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	//cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] vertices;


	//create indirect buffer
	DrawElementsIndirectData indirectData;
	indirectData.count = numElements;
	indirectData.primCount = 1;
	indirectData.firstIndex = 0;
	indirectData.baseVertex = 0;
	indirectData.baseInstance = 0;

	glGenBuffers(1, &indirectBufferObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsIndirectData), &indirectData, GL_STATIC_READ);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);


}


void MeshLibrary::render()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
    glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}

