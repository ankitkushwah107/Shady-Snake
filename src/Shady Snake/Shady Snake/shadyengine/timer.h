
#ifndef INC_SHADY_ENGINE_TIMER_H
#define INC_SHADY_ENGINE_TIMER_H




//C++ headers
#include<memory>
#include<chrono>




namespace shady_engine
{

	class timer
	{


	public:

		timer();

		void init();

		void update();
	
		inline double get_elapsed_time() const {
			return mElapsedTime;
		}

		inline unsigned int get_FPS() const {
			return mFPS;
		}



	private:

		typedef std::chrono::high_resolution_clock mClock;
		typedef std::chrono::microseconds mMicroseconds;

		//for elapsed time
		mClock::time_point mLast;
		mClock::time_point mCurrent;
		double mElapsedTime;

		//For FPS
		unsigned int mFPS;
		unsigned int mCounter;
		mClock::time_point mLastTime;


		double in_seconds(mClock::duration pDuration) const;
		
	};


}


#endif