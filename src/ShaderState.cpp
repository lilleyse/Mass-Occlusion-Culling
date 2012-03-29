#include "ShaderState.h"

ShaderState::ShaderState()
{

}

void ShaderState::initialize()
{
	glGenProgramPipelines(1, &pipeline);
	glBindProgramPipeline(pipeline);
	glBindProgramPipeline(0);

	//create a very basic shader program
	std::vector<GLuint> shaderList;
	std::string vertexShaderPath = "data/shaders/NoLighting.vert";
	std::string fragShaderPath = "data/shaders/ColorPassthrough.frag";
	shaderList.push_back(loadShader(GL_VERTEX_SHADER, vertexShaderPath));
    shaderList.push_back(loadShader(GL_FRAGMENT_SHADER, fragShaderPath));

    basicProgram = createProgram(shaderList);
	
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT, basicProgram);
}

void ShaderState::prepareForRender()
{
	glBindProgramPipeline(pipeline);
}


const char* ShaderState::getShaderName(GLenum eShaderType)
{
    switch(eShaderType)
    {
    case GL_VERTEX_SHADER:
        return "vertex";
        break;
    case GL_GEOMETRY_SHADER:
        return "geometry";
        break;
    case GL_FRAGMENT_SHADER:
        return "fragment";
        break;
    }

    return 0;
}

GLuint ShaderState::createShader(GLenum eShaderType, const std::string &strShaderFile, const std::string &strShaderName)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, (const GLchar**)&strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        fprintf(stderr, "Compile failure in %s shader named \"%s\". Error:\n%s\n",
                getShaderName(eShaderType), strShaderName.c_str(), strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

GLuint ShaderState::loadShader(GLenum eShaderType, std::string& strShaderFilename)
{
    std::string filePath = Utils::getFilePath(strShaderFilename);

    std::ifstream shaderFile(filePath.c_str());
    if(!shaderFile.is_open())
    {
        fprintf(stderr, "Cannot load the shader file \"%s\" for the %s shader.\n",
                filePath.c_str(), getShaderName(eShaderType));
        return 0;
    }
    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();

    return createShader(eShaderType, shaderData.str(), strShaderFilename);
}

GLuint ShaderState::createProgram(const std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();
	glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
	{
		GLuint shaderObject = shaderList[iLoop];
        glAttachShader(program, shaderObject);
		glDeleteShader(shaderObject);
	}

    glLinkProgram(program);

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    return program;
}
