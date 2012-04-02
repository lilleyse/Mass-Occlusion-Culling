#include "MeshLibrary.h"

MeshLibrary::MeshLibrary()
{

}

MeshLibrary::~MeshLibrary()
{

}


void MeshLibrary::initialize()
{

	/*----------------------------
			Create Meshes
	----------------------------*/

	std::vector<Mesh> meshes;

	float positionData1[] =
    {
		.7f, .7f, -.7f, .7f, -.7f, -.7f, -.7f, -.7f, -.7f, -.7f, .7f, -.7f, .7f, .7f, .7f, -.7f, .7f, .7f, -.7f, -.7f, .7f, .7f, -.7f, .7f, .7f, .7f, -.7f, .7f, .7f, .7f, .7f, -.7f, .7f, .7f, -.7f, -.7f, .7f, -.7f, -.7f,.7f, -.7f, .7f,-.7f, -.7f, .7f,-.7f, -.7f, -.7f,-.7f, -.7f, -.7f,-.7f, -.7f, .7f,-.7f, .7f, .7f,-.7f, .7f, -.7f,.7f, .7f, .7f,.7f, .7f, -.7f,-.7f, .7f, -.7f,-.7f, .7f, .7f
	};

	float normalData1[] =
    {
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	unsigned short elementArray1[] =
    {
       0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15,16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23,
    };

	Mesh mesh1;
	mesh1.positionData = positionData1;
	mesh1.normalData = normalData1;
	mesh1.elementArray = elementArray1;
	mesh1.numVertices = 24;
	mesh1.numElements = 36;
	mesh1.numInstances = 5000;
	meshes.push_back(mesh1);

	//create mesh 2 (isosphere)
	float positionData2[] =
	{
		-0.276385f, -0.85064f, -0.447215f, 0.0f, 0.0f, -1.0f, 0.7236f, -0.52572f, -0.447215f, 0.7236f, 0.52572f, -0.447215f, -0.894425f, 0.0f, -0.447215f, -0.276385f, 0.85064f, -0.447215f, 0.894425f, 0.0f, 0.447215f, 0.276385f, -0.85064f, 0.447215f, -0.7236f, -0.52572f, 0.447215f, -0.7236f, 0.52572f, 0.447215f, 0.276385f, 0.85064f, 0.447215f, 0.0f, 0.0f, 1.0f
	};

	float normalData2[] =
	{
		-0.276385f, -0.85064f, -0.447215f, 0.0f, 0.0f, -1.0f, 0.7236f, -0.52572f, -0.447215f, 0.7236f, 0.52572f, -0.447215f, -0.894425f, 0.0f, -0.447215f, -0.276385f, 0.85064f, -0.447215f, 0.894425f, 0.0f, 0.447215f, 0.276385f, -0.85064f, 0.447215f, -0.7236f, -0.52572f, 0.447215f, -0.7236f, 0.52572f, 0.447215f, 0.276385f, 0.85064f, 0.447215f, 0.0f, 0.0f, 1.0f
	};

	unsigned short elementArray2[] = 
	{
		0, 1, 2, 2, 1, 3, 4, 1, 0, 5, 1, 4, 3, 1, 5, 2, 3, 6, 0, 2, 7, 4, 0, 8, 5, 4, 9, 3, 5, 10, 7, 2, 6, 8, 0, 7, 9, 4, 8, 10, 5, 9, 6, 3, 10, 7, 6, 11, 8, 7, 11, 9, 8, 11, 10, 9, 11, 6, 10, 11
	};

	Mesh mesh2;
	mesh2.positionData = positionData2;
	mesh2.normalData = normalData2;
	mesh2.elementArray = elementArray2;
	mesh2.numVertices = 12;
	mesh2.numElements = 60; 
	mesh2.numInstances = 5000;
	meshes.push_back(mesh2);



	/*
		30,000 triangles
	*/
	std::string filename = "data/meshes/pumpkin.dae";
	ColladaData* data = Loader::readColladaAsset(Utils::getFilePath(filename));
	Mesh mesh3;
	mesh3.positionData = &data->positionData[0];
	mesh3.normalData = &data->normalsData[0];
	mesh3.elementArray = &data->elementArray[0];
	mesh3.numVertices = data->numVertices;
	mesh3.numElements = data->elementArray.size();
	mesh3.numInstances = 5000;
	meshes.push_back(mesh3);

	/*
		14,192 triangles
	*/

	std::string filename2 = "data/meshes/alien.dae";
	ColladaData* data2 = Loader::readColladaAsset(Utils::getFilePath(filename2));
	Mesh mesh4;
	mesh4.positionData = &data2->positionData[0];
	mesh4.normalData = &data2->normalsData[0];
	mesh4.elementArray = &data2->elementArray[0];
	mesh4.numVertices = data2->numVertices;
	mesh4.numElements = data2->elementArray.size();
	mesh4.numInstances = 10000;
	meshes.push_back(mesh4);

	/*------------------------------------
			Lump mesh data together
	--------------------------------------*/

	numMeshes = meshes.size();

	//get the total number of vertices and elements
	totalVertices = 0;
	totalElements = 0;
	totalInstances = 0;
	for(unsigned int i = 0; i < numMeshes; i++)
	{
		totalVertices += meshes[i].numVertices;
		totalElements += meshes[i].numElements;
		totalInstances += meshes[i].numInstances;
	}

	//combine vertex and element data from the different shapes
	int vertexCounter = 0;
	int elementCounter = 0;
	int instanceCounter = 0;

	indirectCommands = new DrawElementsIndirectCommand[numMeshes];
	Vertex* vertices = new Vertex[totalVertices];
	unsigned short* elementArray = new unsigned short[totalElements];

	for(unsigned int i = 0; i < numMeshes; i++)
	{
		//create indirect buffer
		indirectCommands[i].count = meshes[i].numElements;
		indirectCommands[i].primCount = meshes[i].numInstances;
		indirectCommands[i].firstIndex = elementCounter;
		indirectCommands[i].baseVertex = vertexCounter;
		indirectCommands[i].baseInstance = instanceCounter;

		//create vertices
		for(int j = 0; j < meshes[i].numVertices; j++)
		{
			int index = vertexCounter + j;
			vertices[index].x = meshes[i].positionData[j*3+0];
			vertices[index].y = meshes[i].positionData[j*3+1];
			vertices[index].z = meshes[i].positionData[j*3+2];

			vertices[index].nx = meshes[i].normalData[j*3+0];
			vertices[index].ny = meshes[i].normalData[j*3+1];
			vertices[index].nz = meshes[i].normalData[j*3+2];
		}

		//copy over element array into the global element array
		memcpy(&elementArray[elementCounter], meshes[i].elementArray, meshes[i].numElements*sizeof(unsigned short));

		vertexCounter += meshes[i].numVertices;
		elementCounter += meshes[i].numElements;
		instanceCounter += meshes[i].numInstances;
	}
	
	/*-----------------------------------------
			Generate OpenGL buffers and VAO
	------------------------------------------*/

	//array buffer
    glGenBuffers(1, &arrayBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
    glBufferData(GL_ARRAY_BUFFER, totalVertices*sizeof(Vertex), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	//translation data that is sent to the vertex shader as a vertex attribute, filled by OpenCL and never read/written by CPU
    glGenBuffers(1, &drawTransformsBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, drawTransformsBufferObject);
    glBufferData(GL_ARRAY_BUFFER, totalInstances*sizeof(float)*4, 0, GL_STREAM_COPY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //element buffer
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalElements*sizeof(GLushort), elementArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//indirect command buffer
	glGenBuffers(1, &indirectBufferObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, numMeshes*sizeof(DrawElementsIndirectCommand), indirectCommands, GL_STATIC_DRAW);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);



	//create and bind vao
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

	//enable vertex attributes
	glEnableVertexAttribArray(GLuint(POSITION));
	glEnableVertexAttribArray(GLuint(TRANSFORM));
	glEnableVertexAttribArray(GLuint(NORMAL));

    //bind array buffer again
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	size_t offset = sizeof(float)*3;
	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offset));

	//bind transform array buffer again
	glBindBuffer(GL_ARRAY_BUFFER, drawTransformsBufferObject);
	glVertexAttribPointer(TRANSFORM, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(TRANSFORM, 1);
	

	//bind element array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	
	
	//cleanup OpenGL
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	delete[] vertices;
	delete[] elementArray;


	/*-----------------------------------------
		Initialize OpenCL
	------------------------------------------*/

	localWorkSize = 256;

	//create different global work sizes for each mesh, aligned to localWorkSize
	globalWorkSizes = new size_t[numMeshes];
	for(unsigned int i = 0; i < numMeshes; i++)
	{
		int instanceCount = indirectCommands[i].primCount;
		int r =  instanceCount % localWorkSize;
		if(r == 0) 
			globalWorkSizes[i] =  instanceCount;
		else 
			globalWorkSizes[i] = instanceCount + localWorkSize - r;
	}

	//Get an OpenCL platform
    clError = clGetPlatformIDs(1, &clPlatform, NULL);

    if (clError != CL_SUCCESS)
        std::cout << "could not create platform" << std::endl;

    //Get the device - for now just assume that the device supports sharing with OpenGL
    clError = clGetDeviceIDs(clPlatform, CL_DEVICE_TYPE_GPU, 1, &clDevice, NULL);
   
	if (clError != CL_SUCCESS) 
		std::cout << "could not get a GPU device on the platform" << std::endl;

	//Create the context, with support for sharing with OpenGL 
	cl_context_properties props[] = 
    {
        CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(), 
        CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(), 
        CL_CONTEXT_PLATFORM, (cl_context_properties)clPlatform, 
        0
    };
    clGPUContext = clCreateContext(props, 1, &clDevice, NULL, NULL, &clError);
	
	if (clError != CL_SUCCESS)
        std::cout << "could not create a context" << std::endl;

    // Create a command-queue
    clCommandQueue = clCreateCommandQueue(clGPUContext, clDevice, 0, &clError);
    if (clError != CL_SUCCESS)
        std::cout << "could not create command queue" << std::endl;

	// load program source code
    size_t programLength;
	std::string filepath = "data/culling.cl";
	filepath = Utils::getFilePath(filepath);
	char* cSourceCL = loadProgramSource(filepath.c_str(), &programLength);
	if(cSourceCL == NULL)
		std::cout << "could not load program source" << std::endl;
  
    // create the program
    clProgram = clCreateProgramWithSource(clGPUContext, 1, (const char **) &cSourceCL, &programLength, &clError);
    if (clError != CL_SUCCESS)
        std::cout << "could not create program" << std::endl;

    // build the program
    clError = clBuildProgram(clProgram, 0, NULL, "-cl-fast-relaxed-math", NULL, NULL);
    if (clError != CL_SUCCESS)
	{
        std::cout << "could not build program" << std::endl;
		char cBuildLog[10240];
		clGetProgramBuildInfo(clProgram, clDevice, CL_PROGRAM_BUILD_LOG, sizeof(cBuildLog), cBuildLog, NULL);
		std::cout << cBuildLog << std::endl;
	}

    // create the kernel
    clKernel = clCreateKernel(clProgram, "pass_along", &clError);
    if (clError != CL_SUCCESS)
        std::cout << "could not create kernel" << std::endl;


	//fill the transform data with random numbers
	float* translationData = new float[totalInstances*4];
	for(int i = 0; i < totalInstances; i++)
	{
		//translationData[i*4 + 0] = i+1;
		//translationData[i*4 + 1] = i+1;
		//translationData[i*4 + 2] = i+1;
		translationData[i*4 + 0] = glm::compRand1(-500.0f, 500.0f);
		translationData[i*4 + 1] = glm::compRand1(-500.0f, 500.0f);
		translationData[i*4 + 2] = glm::compRand1(-500.0f, 500.0f);
		translationData[i*4 + 3] = 1;
	}

	//initialize openCL buffer that will contain translation data
	inputTranslationData_cl = clCreateBuffer(clGPUContext, CL_MEM_READ_ONLY, totalInstances * sizeof(cl_float) * 4, NULL, &clError);
	if (clError != CL_SUCCESS) 
		std::cout << "could not put data into cl buffer" << std::endl;

	//place transformData into the openCL buffer (source)
	clError = clEnqueueWriteBuffer(clCommandQueue, inputTranslationData_cl, CL_FALSE, 0, totalInstances * sizeof(cl_float) * 4, translationData, 0, NULL, NULL);
	if (clError != CL_SUCCESS)
        std::cout << "could not transfer data from host ptr to device ptr" << std::endl;

	//treat the GL indirect buffer object as a CL buffer
	indirectBuffer_cl = clCreateFromGLBuffer(clGPUContext, CL_MEM_READ_WRITE, indirectBufferObject, &clError);
	if (clError != CL_SUCCESS)
        std::cout << "could not convert GL indirect command buffer buffer to a CL buffer" << std::endl;

	//treat the GL translation buffer as a CL buffer (destination)
	translationBuffer_cl = clCreateFromGLBuffer(clGPUContext, CL_MEM_WRITE_ONLY, drawTransformsBufferObject, &clError);
	if (clError != CL_SUCCESS) 
		std::cout << "could not convert GL translation buffer to a CL buffer" << std::endl;


    // set the args values for the kernel
    clError  = clSetKernelArg(clKernel, 0, sizeof(cl_mem), (void*) &inputTranslationData_cl);
    clError |= clSetKernelArg(clKernel, 1, sizeof(cl_mem), (void*) &translationBuffer_cl);
	clError |= clSetKernelArg(clKernel, 4, sizeof(cl_mem), (void*) &indirectBuffer_cl);

    if (clError != CL_SUCCESS)
        std::cout << "could not set arguments to kernel" << std::endl;

}

//from the Nvidia OpenCL utils
char* MeshLibrary::loadProgramSource(const char* cFilename, size_t* szFinalLength)
{
    // locals 
    FILE* pFileStream = NULL;
    size_t szSourceLength;

    if(fopen_s(&pFileStream, cFilename, "rb") != 0)
	{
		return NULL;
	}

    // get the length of the source code
    fseek(pFileStream, 0, SEEK_END); 
    szSourceLength = ftell(pFileStream);
    fseek(pFileStream, 0, SEEK_SET); 

    // allocate a buffer for the source code string and read it in
    char* cSourceString = (char *)malloc(szSourceLength + 1); 
    if (fread((cSourceString), szSourceLength, 1, pFileStream) != 1)
    {
        fclose(pFileStream);
        free(cSourceString);
        return 0;
    }

    // close the file and return the total length of the string
    fclose(pFileStream);
    if(szFinalLength != 0)
    {
        *szFinalLength = szSourceLength;
    }
    cSourceString[szSourceLength] = '\0';

    return cSourceString;
}


void MeshLibrary::render()
{
	//let gl finish before using its buffers
    glFinish();
	
    clEnqueueAcquireGLObjects(clCommandQueue, 1, &translationBuffer_cl, 0,0,0);
	clEnqueueAcquireGLObjects(clCommandQueue, 1, &indirectBuffer_cl, 0,0,0);

	glm::mat4 MVPTransposed = glm::transpose(Globals::modelViewProjectionMatrix);

	//call kernel for each different mesh type
	for(unsigned int i = 0 ; i < numMeshes; i++)
	{
		//get the offset of the "paramCount" parameter of the indirect draw command
		int indirectCommandOffset = i*5 + 1;
		unsigned int zero = 0;

		//Set paramCount to 0. Blocking
		clEnqueueWriteBuffer(clCommandQueue, indirectBuffer_cl, CL_TRUE, indirectCommandOffset*sizeof(cl_uint), sizeof(cl_uint), &zero, 0, 0, 0);

		int numInstances = indirectCommands[i].primCount;
		size_t offset = indirectCommands[i].baseInstance;


		clSetKernelArg(clKernel, 2, sizeof(cl_uint), &numInstances);
		clSetKernelArg(clKernel, 3, sizeof(cl_uint), &offset);
		clSetKernelArg(clKernel, 5, sizeof(cl_uint), &indirectCommandOffset);
		clSetKernelArg(clKernel, 6, sizeof(cl_float)*16, &MVPTransposed);

		//use mesh specific global work size
		clEnqueueNDRangeKernel(clCommandQueue, clKernel, 1, NULL, &globalWorkSizes[i], &localWorkSize, 0,0,0 );
	}
	clEnqueueReleaseGLObjects(clCommandQueue, 1, &translationBuffer_cl, 0,0,0);
	clEnqueueReleaseGLObjects(clCommandQueue, 1, &indirectBuffer_cl, 0,0,0);
	clFinish(clCommandQueue);


	/*---------------------------------------------------------------
			Uncomment to read how many instances are drawn
	---------------------------------------------------------------*/

	/*
	int drawnInstances = 0;
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
	DrawElementsIndirectCommand* pointer = (DrawElementsIndirectCommand*)glMapBufferRange(GL_DRAW_INDIRECT_BUFFER, 0, sizeof(DrawElementsIndirectCommand)*numMeshes, GL_MAP_READ_BIT);
	for(int i = 0; i < numMeshes; i++)
	{
		drawnInstances += pointer[i].primCount;
	}
	glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);
	std::cout << "Drawing " << drawnInstances << " out of " << totalInstances << " instances" << std::endl;
	*/


	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
    glMultiDrawElementsIndirectAMD(GL_TRIANGLES, GL_UNSIGNED_SHORT, 0, numMeshes, 0);
    glBindVertexArray(0);

	




}

