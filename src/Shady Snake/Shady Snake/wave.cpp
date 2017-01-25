#include "wave.h"

wave::wave(
	std::shared_ptr<shady_engine::texture2D> pTexture,
	std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
	const glm::vec2& pPosition,
	const glm::vec2& pSize,
	float pRange)

	:

	GameEntity(pPosition, pSize),
	collider(pPosition, pSize),
	mRenderer(pRenderer),
	mTexture(pTexture),
	mRange(pRange)
{

}

void wave::tick(float pDt)
{
	mRange -= pDt;
	mSize +=(glm::vec2(100.0f)*pDt);
	collider.update(mPosition - (0.5f*mSize),mSize);
}

void wave::render(const glm::mat4 & pProjection, const glm::mat4 & pView) const
{
	mRenderer->draw_image(
		pProjection, pView, mTexture, mPosition-(0.5f*mSize), mSize, 0.0f
	);
}
