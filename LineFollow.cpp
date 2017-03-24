#include "LineFollow.h"
#include <iostream>
#include "ev3dev.h"
#include <cmath>        // std::abs

using namespace ev3dev;

void LineFollow::debugLightValues(){
	bool escape = false;
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	while(!escape){
		std::cout << s.value() << std::endl;
		escape = button::back.pressed();
	}

}

void LineFollow::vorprojekttag()
{
	double band = 350;
	double edge = 530;
	double leadingSpeed;
	double baseSpeed = 100;
	double leadingPercentage;

	bool escape = false;
	motor a(OUTPUT_D);
	motor b(OUTPUT_A);
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	double val;

	while(!escape){
		val = s.value();
		
		if(val <= band){
			a.set_speed_sp(baseSpeed);
			b.set_speed_sp(baseSpeed-(baseSpeed/1.2));
			
		
		}else{
			leadingPercentage =  std::abs((val-band)/(band-edge));
			leadingSpeed = baseSpeed + ((baseSpeed*leadingPercentage));
			std::cout << leadingPercentage << std::endl;
				
				a.set_speed_sp(-baseSpeed);
				b.set_speed_sp(leadingSpeed);		
		}
			a.run_forever();
			b.run_forever();
		escape = button::back.pressed();
	}
	a.stop();
	b.stop();
	
	
}



