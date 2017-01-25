#ifndef INC_ANIMATION_H
#define INC_ANIMATION_H


#include<glm/glm.hpp>


class animation
{

protected:

	int mMaxCols;
	int mMaxRows;
	int mCurrentCol;
	int mCurrentRow;
	int mFrameDelay;
	int mFrameCounter;

	glm::vec2 mFrameSize;


public:

	animation(
		int pMaxCols,
		int pMaxRows,
		int pFrameDelay,
		const glm::vec2& pFrameSize
	);


	void init(
		int pMaxCols,
		int pMaxRows,
		int pFrameDelay,
		const glm::vec2& pFrameSize
	);

	void update();

};

#endif
