#ifndef INC_GAME_ENTITY_H
#define INC_GAME_ENTITY_H





//C++ headers
#include<memory>


//Third party headers
#include<glm/glm.hpp>
#include"Globals.h"





class GameEntity
{

protected:
	
	glm::vec2 mPosition;
	glm::vec2 mSize;
	glm::vec2 mCenter;

public:

	GameEntity();


	GameEntity(
		const glm::vec2& pPosition,
		const glm::vec2& pSize
	);


	~GameEntity();

	//Getters

	inline glm::vec2& getPosition() 
	{
		return mPosition;
	}

	inline glm::vec2& getSize() 
	{
		return mSize;
	}

	inline glm::vec2& getCenter() 
	{
		return mCenter;
	}


	void setPosition(const glm::vec2& newPosition);

	void updateCenter();


	virtual void tick(float dt);

	virtual void render(
	const glm::mat4& projection,
	const glm::mat4& view
	)const;


};




#endif