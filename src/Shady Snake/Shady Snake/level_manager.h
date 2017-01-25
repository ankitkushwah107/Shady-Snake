#ifndef INC_LEVEL_MANAGER_H
#define INC_LEVEL_MANAGER_H


#include<map>
#include"level.h"
#include"map_loader.h"
#include<shadyengine/shader.h>


class level_manager
{

	//int mCurrentLevelIndex;
	level mLevel;


	//render it beyotch!!

	std::shared_ptr<shady_engine::shader> mShader;
	GLuint mVBO;
	GLuint mVAO;

	GLuint mVBOOffsets;
	GLuint mVBOTexCoords;

public:

	level_manager(float pScaleLevel);
	//will return the current level data

	glm::vec2 getMapSize();
	glm::vec2 getPlayerStart();
	void render(
		const glm::mat4& pProjection,
	const glm::mat4& pView
	);

};

#endif
