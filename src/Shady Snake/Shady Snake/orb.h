#pragma once


#include"GameEntity.h"
#include"AABB.h"
#include<shadyengine/sprite_renderer.h>

class orb : public GameEntity
{
	glm::vec4 mColor;
	float mRadius;
	AABB aabb;
	std::shared_ptr<shady_engine::sprite_renderer> mRenderer;

public:

	orb(
		std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
		const glm::vec2& position,
		float pRadius,
		const glm::vec4& pColor
	);

	
	AABB getCollider()
	{	
		return aabb;
	}


	inline glm::vec4 getColor()
	{
		return mColor;
	}

	void render(
	const glm::mat4& pProjection,
		const glm::mat4& pView
	)const override;
	
};