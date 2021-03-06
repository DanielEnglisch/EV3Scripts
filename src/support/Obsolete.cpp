#include "Obsolete.h"


#define KP 1	
#define KI 0.001
#define KD 0.001
#define SPEED 100

void Obs_LineFollow::follow_line_new_pid(){
	motor d(OUTPUT_D);
    motor a(OUTPUT_A);
	
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	
	int target_light_value = 45; //measure between dark an light
	
	
	/*	ki, kd == 0 -> derivative & integral == off
	 * 	lower kp -> smoother
	 * 	fist adjust kp, then ki and at last kd
	 * 	do not touch integral
	 * */
	/*double kp = 5; //how sharp or smooth corretctions are
	*	double ki = 0.001; //test
			double kd = 0.001; //test
	 * 
	 * 
	 * 
	 * */
	
	double integra = 1;
	bool escape = false;
	double last_error(0);
	int base_speed(SPEED);
	double speed_a =0;
	double speed_b = 0;

	
	while ( !escape ){
		

	//correction =(error*KP)+(integral*Ki)+ derivative*kd;
	
		double sensor_value = s.reflected_light_intensity();
		double error = target_light_value - sensor_value; //bright = 45-100 = -55 ||| dark = 45-0 = 45
		double output_a = (error)*KP;
		integra += error;
		double output_b  = integra*KI;
		double derivative = error - last_error;
		double output_c = derivative*KD;
		double direction = output_a+output_b+output_c;
		//std::cout << sensor_value << '*' << output_a <<  ';' << output_b << ';' << output_c << '#' << direction ;
		//std::cout <<  << std::endl;
		
		//bright = 45-100 = -55 ||| dark = 45-0 = 45

		if(direction == 0){
			speed_a = SPEED;
			speed_b = SPEED;
		}else if(direction > 0){
			//go right
			//get actual speed
			speed_a = SPEED - (direction+55);
			speed_b = SPEED ;
		}else if(direction < 0){
			//go left
			//get actual speed
			speed_a = SPEED ;
			speed_b = SPEED -((-direction)+45);			
		
		}
			
			d.set_speed_sp(-speed_b);
			a.set_speed_sp(-speed_a);
			a.run_forever();
			d.run_forever();
		std::cout << sensor_value<< ';' << direction <<  "     " << -speed_a << ';' << -speed_b << std::endl;
		
		
		
		escape = button::back.pressed();
		last_error=error;
		}	

		a.reset();
		d.reset();
     
}
void Obs_LineFollow::vorprojekttag(){
	double band = 350;
	double edge = 500;
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
			b.set_speed_sp(baseSpeed);
			
		
		}else{
			leadingPercentage =  abs((val-band)/(band-edge));
			leadingSpeed = baseSpeed + ((baseSpeed*leadingPercentage));
			cout << leadingPercentage << endl;
				
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
void Obs_LineFollow::follow_line_p(){
	
	motor a(OUTPUT_A);
	motor d(OUTPUT_D);
	//float white = 53.5; float black = 32.8;
	float white = 379; float black = 492;
	
	//LineFollow::calibrate();	
	float midpoint = ( white - black ) / 2 + black;
	float kp=5; // 5 kind of working
	
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	bool escape(false);
	while(!escape ){
		float value = s.value();
		float correction = kp * ( midpoint - value );
		//std::cout << correction << std::endl; // /10-> -12
		float a_speed =(correction+17)/23;
		float contingent =100 ;
		
	
		
		if (correction < 0){
				//cout << endl << a_speed << value <<  "R" << correction << "  ;   " << -(((correction+12)/22) * SPEED );
				//float motor_speed_a = (contingent/4) * a_speed + (contingent/4)*3;
				//float motor_speed_b = (contingent/4) -motor_speed_a +(contingent/4)*3;
				//cout << motor_speed_a << "  #  " << motor_speed_b << endl;
				cout << "R" << value << "  ; "<< correction << " ; "<<(100+(correction*3)) << endl;
				a.set_speed_sp(-(100+correction));
				d.set_speed_sp(-100);
				d.run_forever();
				a.run_forever();
		}
		else if(correction >0){
			//cout << endl<< a_speed <<  "L"<< correction << "  ;   " << -(((correction+12)/22) * SPEED ) ;
				//float motor_speed_a = (contingent/4) * a_speed +(contingent/4)*3;
				//float motor_speed_b = (contingent/4) -motor_speed_a + (contingent/4)*3;
				
				cout << "L" << value << "  ; "<< correction << " ; "<< (100-(correction)) << endl;
				//cout << motor_speed_a << "  #  " << motor_speed_b << endl;
				a.set_speed_sp(-100);
				d.set_speed_sp(-(100-(correction)));
				d.run_forever();
				a.run_forever();
		}
		else {	a.set_speed_sp(-SPEED);
				d.set_speed_sp(-SPEED);
				d.run_forever();
				a.run_forever();
		}
		
		
		
		//	motor a langsamer wenn  correction >0 
		//moor b langsamer wenn correction <0 
		escape = button::back.pressed();
	}
	
		a.reset();
		d.reset();
     
}