//#include "LineFollow.h"
#include "Claw.h"
#include "support/SensorDebug.h"

int main(){
	//ClawControl
	// Claw c;
	// c.open();
	// c.lift();
	
	// // //Sensor-Debug Class
	// 	 SensorDebug debug_sn;
	// 	 debug_sn.PrintLightValues();
	// // 	// debug_sn.

	// robot he;
	// // //he.read_recepie();
	// he.read_recepie();

	Claw xx;
	xx.lift();
	int timer = time(0);
				while(time(0) <= timer+10);
	
	
	
	return 0;
}	