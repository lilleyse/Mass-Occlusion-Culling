#pragma once

#include "glm/glm.hpp"
#include "MeshLibrary.h"
#include "ShaderState.h"

class MeshLibrary;

namespace Globals
{
	//inside Globals.cpp
	extern glm::mat4 viewMatrix;
	extern glm::mat4 modelViewProjectionMatrix;
	extern MeshLibrary meshLibrary;
	extern ShaderState shaderState;

}