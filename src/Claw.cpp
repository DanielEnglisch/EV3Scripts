#include "Claw.h"

int Claw::wait(){
			int counter(0);
		 	double time_start(time(0));
		 	while(time_start+0.2 >= time(0))counter++;
			 return counter;
}

bool Claw::open(){

			motor small (OUTPUT_C);
			//if(small.position_sp() == -1300) return 0;
			small.set_speed_sp(1000);
			small.set_position_sp(0);
			small.run_to_abs_pos();
				int counter(0);
			while(small.position() < -1) counter++;
}

bool Claw::close(){
			motor small (OUTPUT_C);
			//if(small.position_sp() == 0) return 0;
			small.set_speed_sp(1000);
			small.set_position_sp(-950);
			small.run_to_abs_pos();
				int counter(0);
			while(small.position() > -948) counter++;
}

bool Claw::lift(){
		motor big	(OUTPUT_B);	
		//if(big.position_sp() == -120) return 0;
		big.set_speed_sp(100);
		big.set_position_sp(0);
		big.run_to_abs_pos();
		int counter(0);
		while(big.position() > 5) counter++;
}

bool Claw::lower(){
		motor big (OUTPUT_B);
		std::cout << big.position()<< std::endl;
	//	if(big.position_sp() == 0) return 0;
		big.set_speed_sp(100);
		big.set_position_sp(170);
		big.run_to_abs_pos();
			int counter(0);
		while(big.position() < 118) counter++;
		std::cout << big.position();
	
		}


bool Claw::half_lower(){
		motor big (OUTPUT_B);
		std::cout << big.position()<< std::endl;
	//	if(big.position_sp() == 0) return 0;
		big.set_speed_sp(100);
		big.set_position_sp(100);
		big.run_to_abs_pos();
		wait();
		std::cout << big.position();
		
		}
