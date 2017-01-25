#include "explosion.h"

explosion::explosion(
	glm::vec2 pPosition,
	glm::vec2 pSize,
	std::shared_ptr<shady_engine::texture2D> pSprite,
	std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
	int pRows,
	int pCols,
	int pFrameDelay
)
	:
	GameEntity(pPosition,pSize),
	mSprite(pSprite),
	animation(pCols,pRows,pFrameDelay,glm::vec2(
	(pSprite->get_size().x/(pCols+1)),
	(pSprite->get_size().y / (pRows+1))
	)),
	mRenderer(pRenderer)

{
}

explosion::~explosion()
{
}

void explosion::update()
{
	animation::update();
}

void explosion::render(const glm::mat4 & pProjection, const glm::mat4 & pView)
{
	mRenderer->draw_image_region(
		pProjection,
		pView,
		mSprite,
		glm::vec2(mCurrentCol, mCurrentRow)*mFrameSize,
		mFrameSize,
		mPosition,
		mSize
	);
}
