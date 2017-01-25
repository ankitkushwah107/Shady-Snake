#include "level_manager.h"
#include<shadyengine/resources.h>

using namespace shady_engine;


level_manager::level_manager(float pScaleLevel)
{
	map_loader(mLevel,pScaleLevel);


	mShader = resources::getInstance()->load_shader(
		"shader for level",
		"shaders/level_vs.glsl",
		"shaders/level_fs.glsl");


	float vertexAttrs[] =
	{
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f
	};


	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAttrs), vertexAttrs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

glm::vec2 level_manager::getMapSize()
{
	return mLevel.mMapSize;
}


glm::vec2 level_manager::getPlayerStart()
{
	return mLevel.mPlayerStart;
}


void level_manager::render(
	const glm::mat4& pProjection,
	const glm::mat4& pView
)
{
	for (int i = 0; i < mLevel.mMapLayers; i++)
	{

		glGenBuffers(1, &mVBOOffsets);
		glGenBuffers(1, &mVBOTexCoords);


		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->mVBOTexCoords);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*mLevel.mTexCoords[i].size(), mLevel.mTexCoords[i].data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(1, 1);

		glBindBuffer(GL_ARRAY_BUFFER, this->mVBOOffsets);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*mLevel.mOffsets[i].size(), mLevel.mOffsets[i].data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1);

		glBindVertexArray(0);


		mShader->use();
		mShader->setMat4("projection", pProjection);
		mShader->setMat4("view", pView);
		mShader->set2fv("scale", mLevel.mTileSize);

		mShader->set1i("sprite_sheet", 0);
		glActiveTexture(GL_TEXTURE0);
		mLevel.mTextures[i]->bind();

		glBindVertexArray(mVAO);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, mLevel.mOffsets[i].size());
		glBindVertexArray(0);

		glDeleteBuffers(1, &mVBOTexCoords);
		glDeleteBuffers(1, &mVBOOffsets);


	}

}
