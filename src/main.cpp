#include "LineFollow.h"
#include "Claw.h"
#include "support/SensorDebug.h"

int main(){
	
	Claw c;
	c.open();
	c.lift();

	//Sensor-Debug Class
	SensorDebug debug;
	debug.PrintLightValues();
 
	return 0;
}