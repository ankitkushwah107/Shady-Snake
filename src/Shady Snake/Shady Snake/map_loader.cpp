
//declarations headers
#include "map_loader.h"


#include"tinyxml2.h"
#include"map_loader.h"
#include"tinyxml2.h"
#include<shadyengine/resources.h>
#include"Level.h"


using namespace tinyxml2;
using namespace shady_engine;


void map_loader(level& pLevel,float pScaleLevel)
{
	XMLDocument doc;

	if (doc.LoadFile("levels/level.tmx") != XML_SUCCESS)
		throw std::runtime_error("failed to load level!");


	XMLElement* map = doc.FirstChildElement("map");
	int mapWidth = map->IntAttribute("width");
	int mapHeight = map->IntAttribute("height");

	pLevel.mMapSize = glm::vec2(mapWidth, mapHeight)*pScaleLevel;
	pLevel.mTileSize = glm::vec2(pScaleLevel);
	
	std::map<int, XMLElement*> tilesets;
	XMLElement* tileset = map->FirstChildElement("tileset");
	int tilesetCounter = 0;
	while (tileset) {
		tilesets[tilesetCounter++] = tileset;
		tileset = tileset->NextSiblingElement("tileset");
	}

	int layerCounter = 0;

	XMLElement* layer = map->FirstChildElement("layer");

	while (layer)
	{
		float tileWidth = tilesets[layerCounter]->IntAttribute("tilewidth");
		float tileHeight = tilesets[layerCounter]->IntAttribute("tileheight");
		float imageWidth = tilesets[layerCounter]->FirstChildElement("image")->IntAttribute("width");
		float imageHeight = tilesets[layerCounter]->FirstChildElement("image")->IntAttribute("height");
		const char* imageSource = tilesets[layerCounter]->FirstChildElement("image")->Attribute("source");
		
		pLevel.mTextures[layerCounter] = resources::getInstance()->load_texture("texture"+std::to_string(layerCounter),
			imageSource,
			GL_RGBA);

		int tileColumns = tilesets[layerCounter]->IntAttribute("columns");

		XMLElement* tile = layer->FirstChildElement("data")->FirstChildElement("tile");

		int tileCounter = 0;

		while (tile)
		{

			int row = tileCounter / mapWidth;
			int col = tileCounter % mapWidth;
			

			pLevel.mOffsets[layerCounter].push_back(glm::vec2(col,row)*pScaleLevel);

			int gid = tile->IntAttribute("gid")-tilesets[layerCounter]->IntAttribute("firstgid");
		

			glm::vec4 texCoord;
			texCoord.x = ((gid%tileColumns)*tileWidth) / imageWidth;
			texCoord.y = ((gid/tileColumns)*tileHeight) / imageHeight;
			texCoord.z = tileWidth / imageWidth;
			texCoord.w = tileHeight / imageHeight;

			pLevel.mTexCoords[layerCounter].push_back(texCoord);

			tileCounter++;
			tile = tile->NextSiblingElement("tile");
			
		}

		layer = layer->NextSiblingElement("layer");
		layerCounter++;

	}

	pLevel.mMapLayers = layerCounter;

	//Extracting objects
	XMLElement* objectGroup = map->FirstChildElement("objectgroup");
	while (objectGroup)
	{
		std::string objectGroupName = objectGroup->Attribute("name");


		if (objectGroupName == "playerposition")
		{

			XMLElement* object = objectGroup->FirstChildElement("object");
			pLevel.mPlayerStart = glm::vec2(
			object->IntAttribute("x"),
				object->IntAttribute("y")
			);
		
		}
		
		objectGroup = objectGroup->NextSiblingElement("objectgroup");
	}
	

}
 


