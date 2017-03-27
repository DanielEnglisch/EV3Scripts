#include "debug.h"


void DEBUG::debugColorValue(){
	bool escape = false;
	 color_sensor cs(INPUT_3);
	cs.set_mode(color_sensor::mode_col_reflect);
	while(!escape){
		std::cout << cs.reflected_light_intensity() << std::endl;
		escape = button::back.pressed();
	}
}


void DEBUG::debugGyroValues(){
	bool escape = false;
	gyro_sensor s(INPUT_4);
	while(!escape){
		std::cout << s.value() << std::endl;
		escape = button::back.pressed();
	}

}


void DEBUG::debugLightValues(){
	bool escape = false;
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	while(!escape){
		std::cout << s.value() << std::endl;
		escape = button::back.pressed();
	}

}

void DEBUG::debugInfraredValues(){
	bool escape = false;
	infrared_sensor s(INPUT_1);
	while(!escape){
		std::cout << s.proximity() << std::endl;
		escape = button::back.pressed();
	}

}
