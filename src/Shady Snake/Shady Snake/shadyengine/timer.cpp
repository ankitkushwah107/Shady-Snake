//Declaration header
#include"timer.h"


//Exposing namespace
using namespace std::chrono;




namespace shady_engine
{


	//Private functions


	double timer::in_seconds(mClock::duration pDuration) const
	{
		return (duration_cast<microseconds>(pDuration).count() / 1000000.0);
	}


	timer::timer()
	{
		init();
	}



	//Public functions
	
	void timer::init()
	{
		mLast = mClock::now();
		mLastTime = mClock::now();

		mCounter = 0;
		mFPS = 0;
	}


	void timer::update()
	{

		//Updating mElapsedTime
		mCurrent = mClock::now();
		mElapsedTime = in_seconds(mCurrent-mLast);
		mLast = mCurrent;

		//Updating fps

		mCounter++;
		if (in_seconds(mCurrent - mLastTime) > 1.0f)
		{
			mFPS = mCounter;
			mCounter = 0;
			mLastTime = mCurrent;
		}

	}


}