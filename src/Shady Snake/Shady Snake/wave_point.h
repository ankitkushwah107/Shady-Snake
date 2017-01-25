#pragma once



#include"GameEntity.h"
#include"AABB.h"
#include<shadyengine/sprite_renderer.h>
#include<shadyengine/texture2D.h>


class wave_point : public GameEntity
{

	std::shared_ptr<shady_engine::texture2D> mTexture;
	std::shared_ptr<shady_engine::sprite_renderer> mRenderer;
	AABB collider;
	
public:

	wave_point(
		std::shared_ptr<shady_engine::texture2D> pTexture,
	std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
	const glm::vec2& pPosition,
		const glm::vec2& pSize
	);

	AABB getCollider()
	{
		return collider;
	}


	void render(
	const glm::mat4& pProjection,
		const glm::mat4& pView
	)const override;


};