#include "support/SensorDebug.h"

int main(){
/*
	int turning = 100;
	motor a(OUTPUT_A);
	motor d(OUTPUT_D);

	a.set_speed_sp(200);
	d.set_speed_sp(200);
	d.set_time_sp(turning);
	d.set_time_sp(-turning);
a.run_forever();
d.run_forever();
	//a.pause();
	//d.pause();
	//a.stop();
	//d.stop();

	int counter(0);
		 	int time_start(time(0));
		 	while(time_start+2 >= time(0))counter++;
*/
	//robot x;
	//x.read_recepie();
	SensorDebug sd;
	sd.PrintLightValues();

	return 0;
}	