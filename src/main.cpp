#include "LineFollow.h"
//#include "Claw.h"
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

	robot he;
	// //he.read_recepie();
	he.follow_line_d();
	return 0;
}	