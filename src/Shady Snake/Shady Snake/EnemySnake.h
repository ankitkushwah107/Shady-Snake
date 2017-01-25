#pragma once


#include<glm/glm.hpp>
#include"AABB.h"
#include<shadyengine/sprite_renderer.h>
#include<shadyengine/texture2D.h>
#include<vector>


class EnemySnake
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

	EnemySnake(
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


	~EnemySnake();

	void pushNewBlock();


	void set_secured(bool what)
	{
		mSecured = what;
	}

	inline glm::vec2 getHeadPosition()
	{
		return (*mBlocks.begin()).position;
	}

	inline glm::vec2 getSize()
	{
		return mSize;
	}

	std::vector<Block>& getBlocks()
	{
		return mBlocks;
	}

	bool is_secured()
	{
		return mSecured;
	}
	inline glm::vec4 getColor()
	{
		return mColor;
	}

	void negateVelocity();


	void set_back()
	{
		Block head = (*mBlocks.begin());
		head.position = head.lastPosition;
	}


	AABB getHeadCollider()
	{
		return (*mBlocks.begin()).collider;
	}
	inline glm::vec2 getHeadCenter()
	{
		return (*mBlocks.begin()).center;
	}

	void tick(float pDT);

	void render(
		const glm::mat4& pProjection,
		const glm::mat4& pView
	);


private:


	//time
	float mUpdateVelocityTime;

	float mRadius;
	glm::vec4 mColor;
	glm::vec2 mSize;
	glm::vec2 mSpeed;
	std::shared_ptr<shady_engine::sprite_renderer> mRenderer;
	std::shared_ptr<shady_engine::texture2D> mTexture;



	bool mSecured;
	std::vector<Block> mBlocks;


};
