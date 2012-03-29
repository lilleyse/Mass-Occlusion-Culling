#pragma once

#include "Mesh.h"
#include <vector>

class MeshLibrary
{
public:

	MeshLibrary();
	~MeshLibrary();

	void initialize();
	void render();

	std::vector<Mesh*> meshes;

	Mesh* getMesh(int number);



};
