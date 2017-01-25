#include "EnemySnake.h"

#include<shadyengine/random.h>

using namespace shady_engine;


EnemySnake::EnemySnake(
	std::shared_ptr<shady_engine::sprite_renderer> pRenderer,
	std::shared_ptr<shady_engine::texture2D> pTexture,
	const glm::vec2& pHeadPosition,
	const glm::vec2& pHeadVelocity,
	float pSpeed,
	float pRadius,
	int pStartLength,
	const glm::vec4& pColor,
	bool pSecured
)
	:
	mRenderer(pRenderer),
	mRadius(pRadius),
	mSize(2 * mRadius),
	mColor(pColor),
	mSpeed(pSpeed),
	mTexture(pTexture),
	mSecured(pSecured)


{

	mUpdateVelocityTime = random::getInstance()->real(3.0f, 6.0f);

	Block head;
	head.position = pHeadPosition;
	head.velocity = pHeadVelocity;
	head.center = head.position + (mSize*.5f);
	head.collider = AABB(head.position, mSize);
	mBlocks.push_back(head);

	for (int i = 0; i < pStartLength; i++)
		pushNewBlock();

}

EnemySnake::~EnemySnake()
{
	mBlocks.clear();
}

void EnemySnake::pushNewBlock()
{
	Block lastBlock = (*(mBlocks.end() - 1));
	Block newBlock;
	newBlock.position = lastBlock.position + (-lastBlock.velocity*10.0f);
	newBlock.center = newBlock.position + (mSize*.5f);
	newBlock.collider = AABB(newBlock.position, mSize);
	mBlocks.push_back(newBlock);
}


void EnemySnake::negateVelocity()
{
	Block& head = (*mBlocks.begin());
	head.velocity *= -1.0f;
}


void EnemySnake::tick(float pDT)
{

	Block& head = (*mBlocks.begin());

	mUpdateVelocityTime -= pDT;

	if (mUpdateVelocityTime <= 0.0f)
	{

		float angle = random::getInstance()->real(0.0f,360.0f);

		head.velocity = glm::vec2(
			cos(glm::radians(angle)), sin(glm::radians(angle)));

		mUpdateVelocityTime = random::getInstance()->real(3.0f, 6.0f);
	}
	
	
	head.lastPosition = head.position;
	head.position += ((head.velocity*mSpeed)*pDT);
	head.center = head.position + (mSize*.5f);
	head.collider.update(head.position, mSize);

	for (auto iter = (mBlocks.begin() + 1); iter != mBlocks.end(); iter++)
	{
		Block& child = (*iter);
		Block& parent = (*(iter - 1));

		child.velocity = glm::normalize(
			parent.center - child.center
		);

		child.lastPosition = child.position;
		child.position = parent.position + (-child.velocity*10.0f);
		child.center = child.position + (mSize*0.5f);
		child.collider.update(child.position, mSize);

	}

}

void EnemySnake::render(const glm::mat4 & pProjection, const glm::mat4 & pView)
{

	auto head = *(mBlocks.begin());
	mRenderer->draw_image(pProjection, pView, mTexture, head.position, mSize, 0.0f);
}
