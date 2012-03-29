#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

#define DEGREE_TO_RAD .0174532777f

#ifdef _WIN32
#define FILE_SLASH '\\'
#else
#define FILE_SLASH '/'
#endif //WIN32


namespace Utils
{
	//math utils
	void printMatrix(glm::mat4& matrix);
	void printVec3(glm::vec3& vector);
	void printVec4(glm::vec4& vector);

	//file utils
	std::string getFilePath(std::string& subFolder);
}
