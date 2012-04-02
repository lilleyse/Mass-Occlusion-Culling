#include "Loader.h"

Loader::Loader()
{

}

std::vector<float> Loader::parsePositionData(const std::string& configData, size_t size, float& width, float& height, float& depth)
{
    float xMin = FLT_MAX;
	float yMin = FLT_MAX;
	float zMin = FLT_MAX;

    float xMax =  -FLT_MAX;
    float yMax =  -FLT_MAX;
    float zMax =  -FLT_MAX;

    std::vector<float> floats;
    floats.reserve(size);
    char* cstr;
    char* p;
    cstr = new char [configData.size()+1];
    strcpy (cstr, configData.c_str());

    p = strtok (cstr," ");
    while (p!=0)
    {
		//convert strings to floats
        float x = (float)std::atof(p);
        p=strtok(0," ");
        float y = (float)std::atof(p);
        p=strtok(0," ");
        float z = (float)std::atof(p);
        p=strtok(0," ");

        floats.push_back(x);
        floats.push_back(y);
        floats.push_back(z);

		//test for the min and max x,y,z dimensions
        if(x < xMin) xMin = x;
        else if(x > xMax) xMax = x;
        if(y < yMin) yMin = y;
        else if(y > yMax) yMax = y;
        if(z < zMin) zMin = z;
        else if(z > zMax) zMax = z;
    }
    delete[] cstr;
    delete[] p;

    width = xMax - xMin;
    height = yMax - yMin;
    depth = zMax - zMin;

    return floats;
}


std::vector<float> Loader::parseDataIntoFloats(const std::string& configData, size_t size)
{
    std::vector<float> floats;
    floats.reserve(size);
    char* cstr;
    char* p;
    cstr = new char [configData.size()+1];
    strcpy (cstr, configData.c_str());

    p = strtok (cstr," ");
    while (p!=0)
    {
        floats.push_back((float)std::atof(p));
        p=strtok(0," ");
    }
    delete[] cstr;
    delete[] p;

    return floats;
}

std::vector<unsigned short> Loader::parseDataIntoUShorts(const std::string& configData, size_t size)
{
    std::vector<unsigned short> ushorts;
    ushorts.reserve(size);
    char* cstr;
    char* p;
    cstr = new char [configData.size()+1];
    strcpy (cstr, configData.c_str());

    p = strtok (cstr," ");
    while (p!=0)
    {

        ushorts.push_back((unsigned short)std::atoi(p));
        p=strtok(0," ");
    }
    delete[] cstr;
    delete[] p;

    return ushorts;
}


void Loader::loadGeometry(domGeometry* geom, ColladaData* outputData)
{
	bool sourcesLoaded = false;

	std::vector<GLushort> elementArray;


	//loop over the triangle draw commands on this geometry
	for (size_t i = 0; i < geom->getMesh()->getTriangles_array().getCount(); i++) {
			
		domTriangles* triangleDraw = geom->getMesh()->getTriangles_array()[i];
			
		//only load the source data if the source data hasn't already been loaded.
		//multiple triangle draw calls will end up referencing the same data
		if(!sourcesLoaded)
		{
			sourcesLoaded = true;

			//loop over the source inputs (positions, normals, tex coords) for this draw call
			for (size_t i = 0; i < triangleDraw->getInput_array().getCount(); i++) {
				
				domInputLocalOffset* input = triangleDraw->getInput_array()[i];
				std::string semantic = input->getSemantic();
				
				if(semantic == "VERTEX")
				{
					domVertices* vertexSource = daeSafeCast<domVertices>(input->getSource().getElement());
					domSource* positionsSource = daeSafeCast<domSource>(vertexSource->getInput_array()[0]->getSource().getElement());

					std::string positionsData = positionsSource->getFloat_array()->getCharData();
					unsigned int size = (unsigned int)positionsSource->getFloat_array()->getCount();
					float width;
					float height;
					float depth;

					//set the positions for the output mesh
					outputData->positionData = parsePositionData(positionsData, size, width, height, depth);
					outputData->numVertices = size/3;

					//set the dimensions for the output mesh
					outputData->width = width;
					outputData->height = height;
					outputData->depth = depth;
					

				}
				else if(semantic == "NORMAL")
				{
					domSource* normalsSource = daeSafeCast<domSource>(input->getSource().getElement());
					std::string normalsData = normalsSource->getFloat_array()->getCharData();
					unsigned int size = (unsigned int) normalsSource->getFloat_array()->getCount();

					//set the normals for the output mesh
					outputData->normalsData = parseDataIntoFloats(normalsData, size);
				}
				else if(semantic == "TEXCOORD")
				{
					domSource* textureSource = daeSafeCast<domSource>(input->getSource().getElement());
					std::string textureData = textureSource->getFloat_array()->getCharData();
					unsigned int size = (unsigned int) textureSource->getFloat_array()->getCount();
					outputData->textureData = parseDataIntoFloats(textureData, size);
					
					//TODO: loading image in a very hardcoded fashion...only works if one image is present in the collada file
					
					domImage* textureImage = daeSafeCast<domImage>(geom->getParentElement()->getParentElement()->getDescendant("image"));
					std::string filepath = textureImage->getInit_from()->getCharData();
					unsigned int namePos = filepath.find_last_of('/') + 1;
					filepath = filepath.substr(namePos);
					std::cout << filepath << std::endl;
					outputData->textureFileName = filepath;
				}
			}
		}

		//look at the index array
		unsigned int numIndices = (unsigned int) triangleDraw->getCount()*3;
		std::string indexArrayData = triangleDraw->getP()->getCharData();

		//set the index array for the output mesh
		std::vector<GLushort> elementArrayAdd = parseDataIntoUShorts(indexArrayData, numIndices);
		elementArray.insert(elementArray.end(), elementArrayAdd.begin(), elementArrayAdd.end());
			

	}

	//set the draw type for the output mesh
	outputData->primitiveType = GL_TRIANGLES;
	outputData->elementArray = elementArray;
	
}

ColladaData* Loader::readColladaAsset(std::string& fileName)
{
	ColladaData* outputData = new ColladaData();

	DAE dae;
	//std::string filename = Utils::getFilePath("data/test.dae");

	daeElement* root = dae.open(fileName);
	if (!root) {
		std::cout << "Document import failed.\n";
		return 0;
	}


	domVisual_scene* visualScene = daeSafeCast<domVisual_scene>(root->getDescendant("visual_scene"));
	domNode_Array& nodes = visualScene->getNode_array();
	for (size_t i = 0; i < nodes.getCount(); i++)
	{

		//if this node is a geometry node
		if(nodes[i]->getInstance_geometry_array().getCount() == 1)
		{
			domInstance_geometry* instanceGeom = nodes[i]->getInstance_geometry_array()[0];
			domGeometry* geom = daeSafeCast<domGeometry>(instanceGeom->getUrl().getElement());
			loadGeometry(geom, outputData);
		}
	}
	
	return outputData;


}
