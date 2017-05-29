#include "SensorDebug.h"

void SensorDebug::PrintColorValue(){
	color_sensor cs(INPUT_3);
	cs.set_mode(color_sensor::mode_col_color);
	
	while(button::back.pressed()){
		std::cout << std::get<0>(cs.raw())<<  ";"<< std::get<1>(cs.raw()) << ";"<< std::get<2>(cs.raw())<< std::endl;
	//std::cout << cs.value() << std::endl;
	}
}


void SensorDebug::PrintGyroValues(){
	gyro_sensor s(INPUT_4);
	while(button::back.pressed()){
		std::cout << "GyroSensor: " << s.value() << std::endl;
	}

}


void SensorDebug::PrintLightValues(){
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	while(button::back.pressed()){
		std::cout << "TrackingSensor: " << s.value() << std::endl;
	}

}

void SensorDebug::PrintInfraredValues(){
	infrared_sensor s(INPUT_1);
	
//	s.set_mode(infrared_sensor::mode_ir_cal);
	
	s.set_mode(infrared_sensor::mode_ir_prox);
	
	while(button::back.pressed()){
	int avg(0);
		for(int i=0; i <=10;++i)  avg +=s.proximity();
		std::cout << "Proximity: "<<  avg/11 << " ;" << std::endl;
	}
}
void SensorDebug::detect_stone_ir(){
	infrared_sensor s(INPUT_1);
	s.set_mode(infrared_sensor::mode_ir_prox);
	int ir_val(-1);
	int deviation(10);
	int counter(0);
	while(button::back.pressed()|| !(ir_val != -1 && ( ir_val >= s.value()+deviation) || ( ir_val <= s.value()-deviation))){
		std::cout << "DRIVE!!! : "<< s.value() <<';'<< counter++<< std::endl;
		ir_val = s.value();
	}

	//Black 366
	//Silver 767

}
