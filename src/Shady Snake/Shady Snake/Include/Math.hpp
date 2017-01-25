#ifndef INC_GPENGINE_GPMATH_MATH_H
#define INC_GPENGINE_GPMATH_MATH_H


	namespace GPMath
	{
	const float PIE = 3.1415926535f;
	
	//calculates the proper index in matrix
	inline int index(int row,int col) 
	{
		return row*4+col;
	}


	//one radian
	inline float oneRadian()
	{
		return (180/PIE);
	}


	//converts degrees to radians
	inline float radians(float angleInDegree)
	{
		return (angleInDegree/oneRadian());
	}

	
	//converts radians to degrees
	inline float degrees(float angleInRadian)
	{
		return (angleInRadian*oneRadian());
	}

	
	//Maps values from one range to another
	inline float mapToRange(float srcMin,float srcMax,float destMin,float destMax,float input)
	{
		float slope = (destMax-destMin)/(srcMax-srcMin);
		return (destMin+(slope*input));
	}

	}


#endif