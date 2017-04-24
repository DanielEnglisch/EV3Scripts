#if !defined DEBUG_H
#define DEBUG_H
	
	#include <iostream>
	#include "ev3dev.h"

	using std::cout; using std::endl;
	using namespace ev3dev;
	
	class SensorDebug
	{
		public:
			void PrintColorValue();			//BrickColorDetection
			void PrintInfraredValues();		//ProximitySensor
			void PrintGyroValues();			//GyroSensor
			void PrintLightValues();		//LineFollowSensor
	};

#endif