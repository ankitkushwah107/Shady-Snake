#pragma once


#include<glm/glm.hpp>


class AABB
{

public:

	glm::vec2 mPosition;
	glm::vec2 mSize;


	AABB()
	{

	}


	AABB(
	const glm::vec2& pPosition,
		const glm::vec2& pSize
	);


	AABB(
		float pX, float pY, float pWidth, float pHeight
	);

	~AABB();

	void init(
		const glm::vec2& pPosition,
		const glm::vec2& pSize
	);

	void destroy();
	

	void update(
		const glm::vec2& pPosition,
		const glm::vec2& pSize
	);


	bool colliding_with(const AABB& other) const;

};