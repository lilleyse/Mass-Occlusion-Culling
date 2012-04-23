#pragma once

#include <glew/glew.h>
#include <glew/wglew.h>
#include "Globals.h"
#include <glm/gtc/type_precision.hpp>

class Transparency
{
public:

	void initTransparency();
	void reshapeTransparency(int width, int height);
	void prepareTransparency(int width, int height);
	void finalizeTransparency();

	//screen covering quad stuff
	GLuint vertexArrayObject;
	GLuint arrayBufferObject;
	GLuint elementBufferObject;

	GLuint transparencyResolveProgram;

	GLuint* zeroArrayForHeadsArray;
	GLuint headsArray;
	GLuint globalsDataBufferObject;
	GLuint globalsDataTextureBuffer;
	GLuint nodeCounter;
	int predictedNumberOfFragments;

};