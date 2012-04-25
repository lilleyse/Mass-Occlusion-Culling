#include "Transparency.h"


void Transparency::initTransparency()
{

	/*-----------------------------------
		Create screen covering quad
	------------------------------------*/

	
	unsigned short indexes[] =
    {
        0, 1, 2,
        2, 3, 0
    };

	//clip space positions
	float vertices[] =
    {
        -1, 1, -1,
		-1, -1, -1,
		1, -1, -1,
		1, 1, -1
    };

	//array buffer
    glGenBuffers(1, &arrayBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //element buffer
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*6, indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create and bind vao
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

	//enable vertex attributes
	glEnableVertexAttribArray(0);

    //bind array buffer again
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//bind element array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	//cleanup OpenGL
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	

	//create nodeCounter atomic counter
	glGenBuffers(1, &nodeCounter);
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, nodeCounter);
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), 0, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, nodeCounter);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

	//assume that the screen size isnt greater than 1920x1080 (may have to make bigger later)
	zeroArrayForHeadsArray = new unsigned int[1920*1080];
	memset(zeroArrayForHeadsArray, 0, sizeof(unsigned int)*1920*1080);

	glActiveTexture(GL_TEXTURE0 + 1);
	glGenTextures(1, &headsArray);
	glBindTexture(GL_TEXTURE_2D, headsArray);

	//create global data array
	predictedNumberOfFragments = 4193404;
	unsigned int* zeroArray = new unsigned int[predictedNumberOfFragments*4];
	memset(zeroArray, 0, sizeof(unsigned int)*predictedNumberOfFragments*4);
	
	glGenBuffers(1, &globalsDataBufferObject);
    glBindBuffer(GL_TEXTURE_BUFFER, globalsDataBufferObject);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(GLuint)*predictedNumberOfFragments*4, zeroArray, GL_DYNAMIC_DRAW);
	
	delete[] zeroArray;

	glActiveTexture(GL_TEXTURE0 + 2);
	glGenTextures(1, &globalsDataTextureBuffer);
	glBindTexture(GL_TEXTURE_BUFFER, globalsDataTextureBuffer);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32UI, globalsDataBufferObject);
	glBindTexture(GL_TEXTURE_BUFFER, 0);

	//set changes to GL state
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_STENCIL_TEST);
}
void Transparency::reshapeTransparency(int width, int height)
{
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, headsArray);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, zeroArrayForHeadsArray);
}
void Transparency::prepareTransparency(int width, int height)
{
	
	glStencilFunc(GL_ALWAYS, 0x01, 0x01);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, nodeCounter);
	glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(glm::uint32), zeroArrayForHeadsArray);
	
	//fill the heads array with zeros
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, headsArray);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, zeroArrayForHeadsArray);
	glBindImageTexture(1, headsArray, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI); 

	//setup the globals data
	glBindImageTexture(2, globalsDataTextureBuffer, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI);
	
}
void Transparency::finalizeTransparency()
{
	/*glm::uint32 counterAmount;
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, nodeCounter);
	glGetBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(glm::uint32), &counterAmount);
	if(counterAmount > 0)
	{
		std::cout << counterAmount << std::endl;
	}*/
	glStencilFunc(GL_EQUAL, 0x01, 0x01);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glUseProgram(Globals::shaderState.transparencyResolveProgram);
	glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
	
}