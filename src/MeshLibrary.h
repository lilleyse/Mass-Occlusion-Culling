#pragma once

#include <glew/glew.h>
#include <glew/wglew.h>
#include <vector>
#include <iostream>
#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/random.hpp>
#include <CL/opencl.h>
#include "Utils.h"
#include "Globals.h"
#include "Loader.h"


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

struct BufferRegionCL
{
	size_t origin;
	size_t size;
};


class MeshLibrary
{
public:

	MeshLibrary();
	~MeshLibrary();

	void initialize();
	void render();

private:

	//from the Nvidia OpenCL utils
	char* loadProgramSource(const char* cFilename, size_t* szFinalLength);


	//data

	int totalVertices;
	int totalElements;
	int totalInstances;

	unsigned int numMeshes;
	size_t* globalWorkSizes;
	DrawElementsIndirectCommand* indirectCommands;

	//GL buffer objects
	GLuint vertexArrayObject;
	GLuint arrayBufferObject;
	GLuint drawTransformsBufferObject;
	GLuint elementBufferObject;
	GLuint indirectBufferObject;
	GLuint instanceAtomicCounter;

	//CL stuff
	cl_platform_id clPlatform;
	cl_context clGPUContext;
	cl_device_id clDevice;
	cl_command_queue clCommandQueue;
	cl_kernel clKernel;
	cl_mem translationBuffer_cl;
	cl_program clProgram;
	cl_int clError;
	cl_mem inputTranslationData_cl; 
	cl_mem indirectBuffer_cl;
	size_t localWorkSize;
};
