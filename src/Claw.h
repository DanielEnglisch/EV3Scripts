#if !defined CLAW_H
#define CLAW_H
	
	#include "ev3dev.h"
	#include <iostream>
	using namespace ev3dev;	
	
	class Claw
	{
		public:
		
			bool  open();
			bool  close();
			bool  lift();
			bool  lower();
		
	};
#endif
