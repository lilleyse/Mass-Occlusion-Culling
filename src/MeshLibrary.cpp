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

	Mesh* mesh0 = new Mesh(positionData, 24, elementArray, 12);
	meshes.push_back(mesh0);
}


void MeshLibrary::render()
{
	meshes[0]->render();
}

Mesh* MeshLibrary::getMesh(int number)
{
	return meshes[number];
}