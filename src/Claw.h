#if !defined CLAW_H
#define CLAW_H
	
	#include "ev3dev.h"
	
	using namespace ev3dev;	
	
	class Claw
	{
		public:
			
			void  open();
			void  close();
			void  lift();
			void  lower();
		
	};
#endif
