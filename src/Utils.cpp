#include "Utils.h"

namespace Utils
{
	/*----------------------------------
			Math Utils
	------------------------------------*/

	void printMatrix(glm::mat4& matrix)
	{
		std::cout << "==========PRINTING MATRIX==========" << std::endl;
		std::cout << matrix[0].x << " " << matrix[1].x << " " << matrix[2].x << " " << matrix[3].x << std::endl;
		std::cout << matrix[0].y << " " << matrix[1].y << " " << matrix[2].y << " " << matrix[3].y << std::endl;
		std::cout << matrix[0].z << " " << matrix[1].z << " " << matrix[2].z << " " << matrix[3].z << std::endl;
		std::cout << matrix[0].w << " " << matrix[1].w << " " << matrix[2].w << " " << matrix[3].w << std::endl;
	}

	void printVec3(glm::vec3& vector)
	{
		std::cout << vector[0] << " " << vector[1] << " " << vector[2] << std::endl;
	}

	void printVec4(glm::vec4& vector)
	{
		std::cout << vector[0] << " " << vector[1] << " " << vector[2] << " " << vector[3] << std::endl;
	}


	/*----------------------------------
			File Utils
	------------------------------------*/

	std::string formatPath(std::string& path)
	{
		//if we need to format for windows
		if(FILE_SLASH == '\\')
		{
			size_t found = path.find('/');
			while(found != std::string::npos)
			{
				path[found] = FILE_SLASH;
				found = path.find('/');
			}
		}
		return path;
	}

	std::string getFilePath(std::string& subFolder)
	{
		return formatPath(subFolder);
	}

}
