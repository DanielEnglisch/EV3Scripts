#include "SensorDebug.h"

void SensorDebug::PrintColorValue(){
	bool end = true;
	color_sensor cs(INPUT_3);
	cs.set_mode(color_sensor::mode_col_color);
	
	while(end){
	std::cout << "R:"<< std::get<0>(cs.raw())<< std::endl << "G:"<< std::get<1>(cs.raw())<< std::endl << "B:"<< std::get<2>(cs.raw())<< std::endl;
	end = button::button::back.pressed();
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
