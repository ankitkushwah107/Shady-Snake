#pragma once



#include"GameEntity.h"
#include"AABB.h"
#include<shadyengine/sprite_renderer.h>
#include<shadyengine/texture2D.h>


class wave : public GameEntity
{

	std::shared_ptr<shady_engine::texture2D> mTexture;
	std::shared_ptr<shady_engine::sprite_renderer> mRenderer;
	AABB collider;
	float mRange;
	
public:

	wave(
		std::shared_ptr<shady_engine::texture2D> pTexture,
		std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
		const glm::vec2& pPosition,
		const glm::vec2& pSize,
		float pRange
	);

	AABB getCollider()
	{
		return collider;
	}

	bool is_done()
	{
		return (mRange < 0.0f);
	}
	void tick(float pDT) override;

	void render(
		const glm::mat4& pProjection,
		const glm::mat4& pView
	)const override;


};