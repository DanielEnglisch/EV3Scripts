#if !defined CLAW_H
#define CLAW_H
	
	#include "ev3dev.h"
	#include <iostream>
	using namespace ev3dev;	
	
	class Claw
	{
		public:
				Claw(){
						motor small (OUTPUT_B);
						motor middle(OUTPUT_C);
						middle.set_position(0);
						small.set_position(0);		
				}
			 ~Claw(){
				
				lift();
				open();
				wait(); wait(); wait();
				std::cout << "destructor!" << std::endl;	
				//open();
			 }
			int wait();
			bool  open();
			bool  close();
			bool  lift();
			bool  lower();
			bool  half_lower();
		
	};
#endif
