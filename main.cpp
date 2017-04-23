#include "LineFollow.h"
#include "testing.h"
#include "debug.h"

int main(){
	
	//Sensor-Debug Class
	debug sensors;
	
	
	LineFollow_testing testing;
	LineFollow asd;
	
	asd.follow_line_d();
	sensors.ColorValue();
	
	return 0;

}

