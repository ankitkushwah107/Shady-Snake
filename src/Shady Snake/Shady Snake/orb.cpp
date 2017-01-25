#include"orb.h"



orb::orb(
	std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
	const glm::vec2& pPosition,
	float pRadius,
	const glm::vec4& pColor)
	:
	GameEntity(pPosition,glm::vec2(2.0f*pRadius)),
	mRenderer(pRenderer),
	mColor(pColor),
	aabb(pPosition,mSize)
{
}


void orb::render(const glm::mat4 & pProjection, const glm::mat4 & pView) const
{
	mRenderer->draw_circle(pProjection,pView,mPosition,mSize,mColor);
}
