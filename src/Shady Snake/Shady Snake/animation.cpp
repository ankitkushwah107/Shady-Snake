#include "animation.h"

animation::animation(
	int pMaxCols, 
	int pMaxRows, 
	int pFrameDelay,
	const glm::vec2& pFrameSize
)
	:
	mMaxCols(pMaxCols),
	mMaxRows(pMaxRows),
	mCurrentCol(0),
	mCurrentRow(0),
	mFrameDelay(pFrameDelay),
	mFrameCounter(0),
	mFrameSize(pFrameSize)
{
	
}


void animation::init(int pMaxCols, int pMaxRows, int pFrameDelay, const glm::vec2 & pFrameSize)
{
	mMaxCols=pMaxCols;
	mMaxRows=pMaxRows;
	mCurrentCol=0;
	mCurrentRow=0;
	mFrameDelay=pFrameDelay;
	mFrameCounter=0;
	mFrameSize = pFrameSize;
}

void animation::update()
{
	if (++mFrameCounter > mFrameDelay) {
		if (++mCurrentCol > mMaxCols) {
			if (++mCurrentRow > mMaxRows)
				mCurrentRow = 0;

			mCurrentCol = 0;
		}

		mFrameCounter = 0;
	}
}
