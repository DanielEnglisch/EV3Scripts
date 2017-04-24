#include "LineFollow.h"
#include "support/SensorDebug.h"

int main(){
	
	//Sensor-Debug Class
	SensorDebug debug;
	debug.PrintColorValue();
	debug.PrintGyroValues();
	debug.PrintInfraredValues();
	debug.PrintLightValues();

	return 0;

}

