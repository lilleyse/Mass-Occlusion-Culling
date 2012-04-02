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

	//create mesh 1
	float positionData1[] =
    {
		.7f, .7f, -.7f, .7f, -.7f, -.7f, -.7f, -.7f, -.7f, -.7f, .7f, -.7f, .7f, .7f, .7f, -.7f, .7f, .7f, -.7f, -.7f, .7f, .7f, -.7f, .7f, .7f, .7f, -.7f, .7f, .7f, .7f, .7f, -.7f, .7f, .7f, -.7f, -.7f, .7f, -.7f, -.7f,.7f, -.7f, .7f,-.7f, -.7f, .7f,-.7f, -.7f, -.7f,-.7f, -.7f, -.7f,-.7f, -.7f, .7f,-.7f, .7f, .7f,-.7f, .7f, -.7f,.7f, .7f, .7f,.7f, .7f, -.7f,-.7f, .7f, -.7f,-.7f, .7f, .7f
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
	mesh1.numInstances = 2;
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
	mesh2.numInstances = 3000;
	meshes.push_back(mesh2);

	/*------------------------------------
			Lump mesh data together
	--------------------------------------*/

	numMeshes = meshes.size();

	//get the total number of vertices and elements
	int totalVertices = 0;
	int totalElements = 0;
	int totalInstances = 0;
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
			int index = i*vertexCounter + j;
			vertices[index].x = meshes[i].positionData[j*3+0];
			vertices[index].y = meshes[i].positionData[j*3+1];
			vertices[index].z = meshes[i].positionData[j*3+2];
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

    //bind array buffer again
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

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



	//fill the transform data with random numbers
	float* transformData = new float[totalInstances*4];
	for(int i = 0; i < totalInstances; i++)
	{
		transformData[i*4 + 0] = glm::compRand1(-50.0f, 50.0f);
		transformData[i*4 + 1] = glm::compRand1(-50.0f, 50.0f);
		transformData[i*4 + 2] = glm::compRand1(-50.0f, 50.0f);
		transformData[i*4 + 3] = 0;
	}

	//create the cl buffer
	inputTransformData = clCreateBuffer(clGPUContext, CL_MEM_READ_ONLY, totalInstances * sizeof(cl_float) * 4, NULL, &clError);
	if (clError != CL_SUCCESS) 
		std::cout << "could not put data into cl buffer" << std::endl;




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
        std::cout << "could not build program" << std::endl;

    // create the kernel
    clKernel = clCreateKernel(clProgram, "pass_along", &clError);
    if (clError != CL_SUCCESS)
        std::cout << "could not create kernel" << std::endl;

	//treat the GL buffer object as a CL buffer object
	vbo_cl = clCreateFromGLBuffer(clGPUContext, CL_MEM_WRITE_ONLY, drawTransformsBufferObject, NULL);


    // set the args values for the kernel
    clError  = clSetKernelArg(clKernel, 0, sizeof(cl_mem), (void*) &inputTransformData);
    clError |= clSetKernelArg(clKernel, 1, sizeof(cl_mem), (void*) &vbo_cl);
    clError |= clSetKernelArg(clKernel, 2, sizeof(cl_uint), &totalInstances);
    if (clError != CL_SUCCESS)
        std::cout << "could not set arguments to kernel" << std::endl;

   
	//send translation data to the cl buffer
	clError = clEnqueueWriteBuffer(clCommandQueue, inputTransformData, CL_FALSE, 0, totalInstances * sizeof(cl_float) * 4, transformData, 0, NULL, NULL);
	if (clError != CL_SUCCESS)
        std::cout << "could not transfer data from host ptr to device ptr" << std::endl;

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

	//with error checking

    /*glFinish();
    clError = clEnqueueAcquireGLObjects(clCommandQueue, 1, &vbo_cl, 0,0,0);
    if (clError != CL_SUCCESS)
        std::cout << "could not acquire GL object for use" << std::endl;

	clError = clEnqueueNDRangeKernel(clCommandQueue, clKernel, 1, NULL, &globalWorkSize, &localWorkSize, 0,0,0 );
	if (clError != CL_SUCCESS)
        std::cout << "could not run kernel" << std::endl;

	clError = clEnqueueReleaseGLObjects(clCommandQueue, 1, &vbo_cl, 0,0,0);
	if (clError != CL_SUCCESS)
        std::cout << "could not release gl object" << std::endl;

	clFinish(clCommandQueue);*/



    glFinish();
    clEnqueueAcquireGLObjects(clCommandQueue, 1, &vbo_cl, 0,0,0);
	for(unsigned int i = 0 ; i < numMeshes; i++)
	{
		int numInstances = indirectCommands[i].primCount;
		size_t baseInstance = indirectCommands[i].baseInstance;

		clError  = clSetKernelArg(clKernel, 2, sizeof(cl_uint), &numInstances);

		if (clError != CL_SUCCESS)
			std::cout << "could not set arguments to kernel during runtime" << std::endl;

		clEnqueueNDRangeKernel(clCommandQueue, clKernel, 1, &baseInstance, &globalWorkSizes[i], &localWorkSize, 0,0,0 );
	}
	clEnqueueReleaseGLObjects(clCommandQueue, 1, &vbo_cl, 0,0,0);
	clFinish(clCommandQueue);


	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferObject);
	//if meshCount == 1 use glDrawElementsIndirect instead
	//glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT, 0);
    glMultiDrawElementsIndirectAMD(GL_TRIANGLES, GL_UNSIGNED_SHORT, 0, numMeshes, 0);
    glBindVertexArray(0);

	


}

