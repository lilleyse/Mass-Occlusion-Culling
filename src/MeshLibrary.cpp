#include "MeshLibrary.h"

MeshLibrary::MeshLibrary()
{

}

MeshLibrary::~MeshLibrary()
{

}

void MeshLibrary::initialize()
{
	std::vector<Mesh> meshes;

	//create mesh 1
	float positionData1[] =
    {
		.5f, .5f, -.5f, .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f, -.5f, .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f, .5f, .5f, .5f, -.5f, .5f, .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, -.5f, -.5f,.5f, -.5f, .5f,-.5f, -.5f, .5f,-.5f, -.5f, -.5f,-.5f, -.5f, -.5f,-.5f, -.5f, .5f,-.5f, .5f, .5f,-.5f, .5f, -.5f,.5f, .5f, .5f,.5f, .5f, -.5f,-.5f, .5f, -.5f,-.5f, .5f, .5f
	};

	unsigned short elementArray1[] =
    {
       0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15,16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23,
    };

	Mesh mesh1;
	mesh1.positionData = positionData1;
	mesh1.elementArray = elementArray1;
	mesh1.numVertices = 24;
	mesh1.numElements = 36;
	meshes.push_back(mesh1);

	//create mesh 2
	float positionData2[] =
	{
		-0.276385f, -0.85064f, -0.447215f, 0.0f, 0.0f, -1.0f, 0.7236f, -0.52572f, -0.447215f, 0.7236f, 0.52572f, -0.447215f, -0.894425f, 0.0f, -0.447215f, -0.276385f, 0.85064f, -0.447215f, 0.894425f, 0.0f, 0.447215f, 0.276385f, -0.85064f, 0.447215f, -0.7236f, -0.52572f, 0.447215f, -0.7236f, 0.52572f, 0.447215f, 0.276385f, 0.85064f, 0.447215f, 0.0f, 0.0f, 1.0f
	};

	unsigned short elementArray2[] = 
	{
		0, 1, 2, 2, 1, 3, 4, 1, 0, 5, 1, 4, 3, 1, 5, 2, 3, 6, 0, 2, 7, 4, 0, 8, 5, 4, 9, 3, 5, 10, 7, 2, 6, 8, 0, 7, 9, 4, 8, 10, 5, 9, 6, 3, 10, 7, 6, 11, 8, 7, 11, 9, 8, 11, 10, 9, 11, 6, 10, 11
	};

	Mesh mesh2;
	mesh2.positionData = positionData2;
	mesh2.elementArray = elementArray2;
	mesh2.numVertices = 12;
	mesh2.numElements = 60; 
	meshes.push_back(mesh2);


	unsigned int numMeshes = meshes.size();

	//get the total number of vertices and elements
	int totalVertices = 0;
	int totalElements = 0;
	for(unsigned int i = 0; i < numMeshes; i++)
	{
		totalVertices += meshes[i].numVertices;
		totalElements += meshes[i].numElements;
	}

	//combine vertex and element data from the different shapes
	int vertexCounter = 0;
	int elementCounter = 0;
	DrawElementsIndirectCommand* indirectCommands = new DrawElementsIndirectCommand[numMeshes];
	Vertex* vertices = new Vertex[totalVertices];
	unsigned short* elementArray = new unsigned short[totalElements];

	//memcpy(elementArray, meshes[0].elementArray, 36*sizeof(unsigned short));

	for(unsigned int i = 0; i < numMeshes; i++)
	{
		//create indirect buffer
		indirectCommands[i].count = meshes[i].numElements;
		indirectCommands[i].primCount = 1;
		indirectCommands[i].firstIndex = elementCounter;
		indirectCommands[i].baseVertex = vertexCounter;
		indirectCommands[i].baseInstance = 0;

		//create vertices
		for(int j = 0; j < meshes[i].numVertices; j++)
		{
			int index = i*vertexCounter + j;
			vertices[index].x = meshes[i].positionData[j*3+0];
			vertices[index].y = meshes[i].positionData[j*3+1];
			vertices[index].z = meshes[i].positionData[j*3+2];
		}

		//copy over element array into the global element array
		memcpy(&elementArray[elementCounter], meshes[i].elementArray, meshes[i].numElements*sizeof(unsigned short));

		vertexCounter += meshes[i].numVertices;
		elementCounter += meshes[i].numElements;
	}
	


	//create and bind array buffer, set data
    glGenBuffers(1, &arrayBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*totalVertices, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //create and bind element array buffer, set data to the stored element array, then close buffer
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*totalElements, elementArray, GL_STATIC_DRAW);
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

	//generate indirect buffer
	glGenBuffers(1, &indirectBufferObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsIndirectCommand)*numMeshes, indirectCommands, GL_STATIC_READ);
	


	//cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	delete[] vertices;
	delete[] elementArray;
	delete[] indirectCommands;

}


void MeshLibrary::render()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
    glMultiDrawElementsIndirectAMD(GL_TRIANGLES, GL_UNSIGNED_SHORT, 0, 2, sizeof(DrawElementsIndirectCommand));
    glBindVertexArray(0);
}

