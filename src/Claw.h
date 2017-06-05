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
						std::cout << "POS-SMALL MOTOR(open/close) =" << small.position();
						std::cout << "POS-big MOTOR(lift) =" << middle.position();
						
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
