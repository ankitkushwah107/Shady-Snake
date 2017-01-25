//Declaration headers
#include"GameEntity.h"



GameEntity::GameEntity()
{

}

GameEntity::GameEntity(const glm::vec2 & pPosition, const glm::vec2 & pSize)
	:
	mPosition(pPosition),
	mSize(pSize),
	mCenter(pPosition + (0.5f*pSize))
{
}



GameEntity::~GameEntity()
{

}


void GameEntity::setPosition(const glm::vec2& pPosition)
{
	mPosition = pPosition;
}


void GameEntity::updateCenter()
{
	mCenter = mPosition+(.5f*mSize);
}


void GameEntity::tick(float dt)
{

}


void GameEntity::render(
	const glm::mat4& projection,
	const glm::mat4& view
) const 
{

}