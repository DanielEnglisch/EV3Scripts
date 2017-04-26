#include "Claw.h"

bool isOpen = false;
bool isLifted = false;


void Claw::open(){
	if(!isOpen){
		//OPEN CLAW
		isOpen = true;
	}
}

void Claw::close(){
	if(isOpen){
		//CLOSE CLAW
		isOpen = false;
	}
}

void Claw::lift(){
	if(!isLifted){
		//Lift CLAW
		isLifted = true;
	}
}

void Claw::lower(){
	if(isLifted){
		//Lower CLAW
		isLifted = false;
	}
}



