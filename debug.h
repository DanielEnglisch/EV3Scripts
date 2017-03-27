#if !defined DEBUG_H
#define DEBUG_H
	
	#include <iostream>
	#include "ev3dev.h"
	//using ev3dev::motor;
	using std::cout; using std::endl;
	using namespace ev3dev;
	
	class debug
	{
		public:
			void ColorValue();
			void InfraredValues();
			void GyroValues();
			void LightValues();
		
	};


#endif