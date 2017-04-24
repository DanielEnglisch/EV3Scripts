#if !defined LINEFOLLOW_H
#define LINEFOLLOW_H
	
	#include <iostream>
	#include "ev3dev.h"
	#include <cmath>        // std::abs
	
	using namespace ev3dev;
	//using ev3dev::motor;
	using std::cout; using std::endl; using std::abs;
	
	#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
	
	class LineFollow
	{
		public:
			
			void  follow_line_d();
			void  forward_motors(float correction);

		private: //not sure if this is correct
			void  calibrate();
			float floatMap(float vx, float v1, float v2, float n1, float n2);
			void  drive(float steering, float throttle,int mode, motor a, motor b);
		
	};
#endif // LINEFOLLOW_H
