#include "wave_point.h"


wave_point::wave_point(
	std::shared_ptr<shady_engine::texture2D> pTexture,
	std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
	const glm::vec2& pPosition,
	const glm::vec2& pSize)
	:
	GameEntity(pPosition,pSize),
	collider(pPosition,pSize),
	mRenderer(pRenderer),
	mTexture(pTexture)
{
	
}


void wave_point::render(const glm::mat4 & pProjection, const glm::mat4 & pView) const
{
	static float angle = 0;
	angle += 10.0f;
	mRenderer->draw_image(pProjection,pView,mTexture,mPosition,mSize,glm::radians(angle));
}
