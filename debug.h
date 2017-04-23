#if !defined DEBUG_H
#define DEBUG_H
	
	#include <iostream>
	#include "ev3dev.h"

	using std::cout; using std::endl;
	using namespace ev3dev;
	
	class debug
	{
		public:
			void ColorValue(); 		//BrickColorDetection
			void InfraredValues();	//ProximitySensor
			void GyroValues();		//GyroSensor
			void LightValues();		//LineFollowSensor
		
	};


#endif