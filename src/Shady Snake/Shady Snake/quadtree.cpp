#include"Quadtree.h"



quadtree::quadtree(
	int pLevel,
	Rectangle& pBounds
)
	:

	mLevel(pLevel),
	mBounds(pBounds)
{
	mNodes[0] = mNodes[1] = mNodes[2] = mNodes[3] = nullptr;
}



quadtree::~quadtree()
{
	
}




int quadtree::get_index(AABB& collider)
{
	int index = -1;
	

	float xMid = mBounds.x + (mBounds.z / 2.0f);
	float yMid = mBounds.y + (mBounds.w / 2.0f);

	bool top = (collider.mPosition.y < yMid) && (collider.mPosition.y + collider.mSize.y < yMid);
	bool bottom = (collider.mPosition.y > yMid);

	bool left = (collider.mPosition.x < xMid) && (collider.mPosition.x + collider.mSize.x < xMid);
	bool right = (collider.mPosition.x > xMid);
		
	if (top && right) index = 0;
	if (top && left) index = 1;
	if (bottom && left) index = 2;
	if (bottom && right) index = 3;

	return index;

	
}


void quadtree::split()
{
		float subWidth = (mBounds.z / 2.0f);
		float subHeight = (mBounds.w / 2.0f);
		float x = mBounds.x;
		float y = mBounds.y;

		mNodes[0] = new quadtree(mLevel + 1, Rectangle(x + subWidth, y, subWidth, subHeight));
		mNodes[1] = new quadtree(mLevel + 1, Rectangle(x, y, subWidth, subHeight));
		mNodes[2] = new quadtree(mLevel + 1, Rectangle(x, y + subHeight, subWidth, subHeight));
		mNodes[3] = new quadtree(mLevel + 1, Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
}



void quadtree::insert(AABB collider)
{

	if (mNodes[0] != nullptr)
	{
		int index = get_index(collider);
		
		if (index != -1)
			mNodes[index]->insert(collider);

		return;
	}


	objects.push_back(collider);

	if (objects.size() > MAX_OBJECTS && mLevel < MAX_LEVEL)
	{
		if (mNodes[0] == nullptr)
			split();


		for (auto iter = objects.begin(); iter != objects.end();)
		{
			int index = get_index(*iter);

			if (index != -1)
			{
				mNodes[index]->insert(*iter);
				iter = objects.erase(iter);
			}
			else
				iter++;
			
		}

	}

}



void quadtree::retrieve(std::vector<AABB>& colliders, AABB particle)
{

	int index = get_index(particle);

		if (mNodes[0] != nullptr && index != -1)
				mNodes[index]->retrieve(colliders, particle);

		colliders.insert(colliders.end(),objects.begin(),objects.end());
}



void quadtree::clear()
{

	objects.clear();

	for (int i = 0; i < 4; i++)
	{
		if (mNodes[i] != nullptr)
		{
			mNodes[i]->clear();
			delete mNodes[i];
			mNodes[i] = nullptr;
		}
	}

}