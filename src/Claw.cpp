#include "Claw.h"


bool Claw::open(){
			motor small (OUTPUT_B);
			if(small.position_sp() == 0) return 0;
			small.set_speed_sp(1000);
			small.set_position_sp(0);
			small.run_to_abs_pos();	
}

bool Claw::close(){
			motor small (OUTPUT_B);
			if(small.position_sp() == -1300) return 0;
			small.set_speed_sp(1000);
			small.set_position_sp(-1300);
			small.run_to_abs_pos();
			
}

bool Claw::lift(){
		motor big	(OUTPUT_C);	
		//if(big.position_sp() == -120) return 0;
		std::cout << big.position_sp();
		big.set_speed_sp(200);
		big.set_position_sp(-120);
		big.run_to_abs_pos();
		std::cout << big.position_sp();
}

bool Claw::lower(){
		motor big (OUTPUT_C);
		if(big.position_sp() == 0) return 0;
		big.set_speed_sp(50);
		big.set_position_sp(0);
		big.run_to_abs_pos();
		
		}
