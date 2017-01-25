#include "AABB.h"

AABB::AABB(const glm::vec2 & pPosition, const glm::vec2 & pSize)
	:

	mPosition(pPosition),
	mSize(pSize)
{

}

AABB::AABB(float pX, float pY, float pWidth, float pHeight)
	:
	mPosition(pX,pY),
	mSize(pWidth,pHeight)
{

}

AABB::~AABB()
{
}

void AABB::init(const glm::vec2 & pPosition, const glm::vec2 & pSize)
{
	mPosition = pPosition;
	mSize = pSize;
}


void AABB::destroy()
{
}


void AABB::update(const glm::vec2 & pPosition, const glm::vec2 & pSize)
{
	mPosition = pPosition;
	mSize = pSize;
}

bool AABB::colliding_with(const AABB & other) const
{

	bool xCollision = mPosition.x + mSize.x >= other.mPosition.x
		&&
		other.mPosition.x + other.mSize.x >= mPosition.x;

	bool yCollision = mPosition.y + mSize.y >= other.mPosition.y
		&&
		other.mPosition.y + other.mSize.y >= mPosition.y;

	return xCollision && yCollision;
}
