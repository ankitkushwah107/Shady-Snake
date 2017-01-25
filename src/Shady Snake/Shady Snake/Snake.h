#pragma once


#include<glm/glm.hpp>
#include"AABB.h"
#include<shadyengine/sprite_renderer.h>
#include<shadyengine/texture2D.h>
#include<vector>


class Snake
{

public:

	struct Block
	{
		glm::vec2 position;
		glm::vec2 lastPosition;
		glm::vec2 velocity;
		glm::vec2 center;
		AABB collider;
	};

	Snake(
		std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
		std::shared_ptr<shady_engine::texture2D> pTexture,
		const glm::vec2& pHeadPosition,
		const glm::vec2& pHeadVelocity,
		float pSpeed,
		float pRadius,
		int pStartLength,
		const glm::vec4& pColor,
		bool pSecured
	);

	void pushNewBlock();

	std::vector<Block>& getBlocks()
	{
		return mBlocks;
	}

	void onMouseMove(const glm::vec2 pCursorPosition);

	void set_secured(bool what)
	{
		mSecured = what;
	}

	AABB getHeadCollider()
	{
		return (*mBlocks.begin()).collider;
	}

	inline glm::vec2 getHeadCenter()
	{
		return (*mBlocks.begin()).center;
	}

	inline glm::vec2 getSize()
	{
		return mSize;
	}

	inline glm::vec4 getColor()
	{
		return mColor;
	}


	void tick(float pDT);

	void render(
		const glm::mat4& pProjection,
		const glm::mat4& pView
	);

	bool is_secured()
	{
		return mSecured;
	}


private:

	bool mSecured;
	float mRadius;
	glm::vec4 mColor;
	glm::vec2 mSize;
	glm::vec2 mSpeed;
	std::shared_ptr<shady_engine::sprite_renderer> mRenderer;
	std::shared_ptr<shady_engine::texture2D> mTexture;




	std::vector<Block> mBlocks;


};
