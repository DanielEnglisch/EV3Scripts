#if !defined TESTING_H
#define TESTING_H
	
	#include <iostream>
	#include "ev3dev.h"
	//using ev3dev::motor;
	using std::cout; using std::endl;
	using namespace ev3dev;
	
	class DEBUG{
		void debugColorValue();
		void debugInfraredValues();
		void debugGyroValues();
		void debugLightValues();
		
	};


#endif