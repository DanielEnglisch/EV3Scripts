#include "SensorDebug.h"

void SensorDebug::PrintColorValue(){
	bool escape = false;
	 color_sensor cs(INPUT_3);
	cs.set_mode(color_sensor::mode_col_reflect);
	while(!escape){
		std::cout << "ColorSensor: " << cs.reflected_light_intensity() << std::endl;
		escape = button::back.pressed();
	}
}


void SensorDebug::PrintGyroValues(){
	bool escape = false;
	gyro_sensor s(INPUT_4);
	while(!escape){
		std::cout << "GyroSensor: " << s.value() << std::endl;
		escape = button::back.pressed();
	}

}


void SensorDebug::PrintLightValues(){
	bool escape = false;
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	while(!escape){
		std::cout << "TrackingSensor: " << s.value() << std::endl;
		escape = button::back.pressed();
	}

}

void SensorDebug::PrintInfraredValues(){
	bool escape = false;
	infrared_sensor s(INPUT_1);
	while(!escape){
		std::cout << "Proximity: "<< s.proximity() << std::endl;
		escape = button::back.pressed();
	}

}
