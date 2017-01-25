#ifndef INC_QUADTREE_H
#define INC_QUADTREE_H


#include<memory>
#include<vector>
#include<glm/glm.hpp>

#include"AABB.h"



typedef glm::vec4 Rectangle;


class quadtree
{
	
public:


	quadtree()
	{

	}


	quadtree(
		int pLevel,
		Rectangle& pBounds
	);


	void clear();
	
	void insert(AABB particle);

	void retrieve(std::vector<AABB>& colliders,AABB particle);

	~quadtree();
	

private:

	int get_index(AABB& particle);
	void split();


	static const int MAX_OBJECTS = 3;
	static const int MAX_LEVEL = 2;

	int mLevel;

	quadtree* mNodes[4];
	Rectangle mBounds;
	
	std::vector<AABB> objects;

};


#endif