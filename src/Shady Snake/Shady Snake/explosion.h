#ifndef INC_EXPLOSION_H
#define INC_EXPLOSION_H

#include"GameEntity.h"
#include"animation.h"
#include<glm/glm.hpp>
#include<shadyengine/texture2D.h>
#include<shadyengine/shader.h>
#include<shadyengine/sprite_renderer.h>


class explosion : public GameEntity, public animation
{
private:

	std::shared_ptr<shady_engine::texture2D> mSprite;
	std::shared_ptr<shady_engine::sprite_renderer> mRenderer;

public:

	explosion(
		glm::vec2 pPosition,
		glm::vec2 pSize,
		std::shared_ptr<shady_engine::texture2D> pSprite,
		std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
		int pRows,
		int pCols,
		int pFrameDelay
	);

	~explosion();

	bool is_done()
	{
		return ((mCurrentCol == mMaxCols) && (mCurrentRow == mMaxRows));
	}

	void update();

	void render(
		const glm::mat4& pProjection,
		const glm::mat4& pView
	);
};

#endif