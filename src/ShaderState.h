#pragma once
#include <gl3w/gl3w.h>
#include <vector>
#include "Utils.h"
#include <fstream>
#include <sstream>

class ShaderState
{
public:
	ShaderState();
	void initialize();
	void prepareForRender();

	GLuint basicProgram;
	GLuint pipeline;

private:
	//modified from http://arcsynthesis.org/gltut/
    GLuint createProgram(const std::vector<GLuint> &shaderList);
	GLuint loadShader(GLenum eShaderType, std::string& strShaderFilename);
    GLuint createShader(GLenum eShaderType, const std::string &strShaderFile, const std::string &strShaderName);
    const char* getShaderName(GLenum eShaderType);

};