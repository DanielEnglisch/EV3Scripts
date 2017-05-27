#include "SensorDebug.h"

void SensorDebug::PrintColorValue(){
	bool end = true;
	color_sensor cs(INPUT_3);
	cs.set_mode(color_sensor::mode_col_color);
	
	while(end){
	std::cout << std::get<0>(cs.raw())<<  ";"<< std::get<1>(cs.raw()) << ";"<< std::get<2>(cs.raw())<< std::endl;
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
		escape = button::button::back.pressed();
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
