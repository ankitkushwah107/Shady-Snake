#ifndef INC_GLOBALS_HPP
#define INC_GLOBALS_HPP


//C++ Headers
#include<cstdint>


class Globals
{

public:

	//Compile-time constants
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	static const int MAX_KEYS = 4;
	//Enum classes

	enum class Keys :std::int8_t { UP, DOWN, LEFT, RIGHT };

};

#endif