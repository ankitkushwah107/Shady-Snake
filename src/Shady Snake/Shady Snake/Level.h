#ifndef INC_LEVEL_H
#define INC_LEVEL_H


#include<memory>
#include<vector>
#include<map>
#include<glm/glm.hpp>
#include<shadyengine/texture2D.h>

#include"AABB.h"

class level
{

public:


	std::string name;

	glm::vec2 mMapSize;
	glm::vec2 mTileSize;
	int mMapLayers;
	glm::vec2 mPlayerStart;

	//Attributes needed to perform instancing
	std::map<int, std::vector<glm::vec2>> mOffsets;
	std::map<int, std::vector<glm::vec4>> mTexCoords;
	std::map<int, std::shared_ptr<shady_engine::texture2D>> mTextures;

};


#endif
