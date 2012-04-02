#pragma once


#include "Utils.h"
#include "ColladaData.h"

#include <glew/glew.h>
#include <glew/wglew.h>
#include <dae.h>
#include <dom/domCOLLADA.h>




class Loader
{
public:
	Loader();
	static ColladaData* readColladaAsset(std::string& fileName);

private:
	
	static void loadGeometry(domGeometry* geom, ColladaData* outputData);

	//Parses a space-separated string of position data into a vector of floats. Finds the width, height, depth of the given positions
	static std::vector<float> parsePositionData(const std::string& configData, size_t size, float& width, float& height, float& depth);
	static std::vector<float> parseDataIntoFloats(const std::string& configData, size_t size);
	static std::vector<unsigned short> parseDataIntoUShorts(const std::string& configData, size_t size);
	
};



