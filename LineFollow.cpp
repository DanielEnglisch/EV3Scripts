#include "LineFollow.h"
#include <iostream>
#include "ev3dev.h"
#include <cmath>        // std::abs

using namespace ev3dev;
using namespace std;


#define KP 1	
#define KI 0.001
#define KD 0.001
#define SPEED 100

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))



void LineFollow::follow_line_new_pid(){
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


void LineFollow::debugLightValues(){
	bool escape = false;
	light_sensor s(INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	while(!escape){
		std::cout << s.value() << std::endl;
		escape = button::back.pressed();
	}

}

void LineFollow::follow_line_s()
{
	
	motor a (OUTPUT_D);
	motor b (OUTPUT_A);
	light_sensor s (INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	bool escape = false;
	double val;
	float throttle;
	
	while(!escape)
	{
		val = s.value();
		
		drive(val,1,1, a, b);
		
		a.run_forever();
		b.run_forever();
		
		escape = button::back.pressed();
	}
	a.stop();
	b.stop();
}

void LineFollow::drive(float steering, float throttle,int mode, motor a, motor b){
    float motA, motAS, motATS, motB, motBS, motBTS;
	int minSpeed = -200;
	int maxSpeed = 200;

    // if(throttle>0){ //funciona
    //     motATS=constrain(throttle*(1+steering), -1, 1);
    //     motBTS=constrain(throttle*(1-steering), -1, 1);
    // }else{
    //     motATS=constrain(throttle*(1-steering), -1, 1);
    //     motBTS=constrain(throttle*(1+steering), -1, 1);
    // }

    // if(throttle<0){
    //     motATS=constrain(throttle*(1-steering), -1, 1);
    //     motBTS=constrain(throttle*(1+steering), -1, 1);
    // }else{
    //     motATS=constrain(throttle*(1+steering), -1, 1);
    //     motBTS=constrain(throttle*(1-steering), -1, 1);
    // }

	// black 338
	// white 536
	
	steering = floatMap(steering,338,536,-1,1);

    if(mode==1 && throttle<0){
        motATS=constrain(throttle*(1-steering), -1, 1);
        motBTS=constrain(throttle*(1+steering), -1, 1);
    }else{
        motATS=constrain(throttle*(1+steering), -1, 1);
        motBTS=constrain(throttle*(1-steering), -1, 1);
    }

    if(mode==1){
        motAS=+steering*(1-abs(throttle));
        motBS=-steering*(1-abs(throttle));
    }else if(mode==0){
        motAS=0;
        motBS=0;
    }

    motA=constrain(motATS+motAS, -1, 1);
    motB=constrain(motBTS+motBS, -1, 1);

    if(motA>0){
        a.set_speed_sp(floatMap(motA,0,1,minSpeed,maxSpeed));
    }else if(motA<0){
        
        a.set_speed_sp(floatMap(abs(motA),0,1,minSpeed,maxSpeed));
    }else{
        a.set_speed_sp(0);
    }

    if(motB>0){
        b.set_speed_sp(floatMap(motB,0,1,minSpeed,maxSpeed));
    }else if(motB<0){
        b.set_speed_sp(floatMap(abs(motB),0,1,minSpeed,maxSpeed));
    }else{
        b.set_speed_sp(0);
    }
}

float LineFollow::floatMap(float vx, float v1, float v2, float n1, float n2){
	//this function maps vx in the range v1 to v2 to the new range n1 and n2
	
    // v1 start of range, v2 end of range, vx the starting number between the range
    float percentage = (vx-v1)/(v2-v1);
    // n1 start of new range, n2 end of new range
    return (n2-n1)*percentage+n1;
}


void LineFollow::vorprojekttag()
{
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




void  LineFollow::follow_line_p(){
	
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

void  LineFollow::calibrate(){
	float white = 40;
	float black = 30;
}

void LineFollow::forward_motors(float correction){
			motor a(OUTPUT_A);
	motor d(OUTPUT_D);
		correction *= 10;
		if(correction > 0) {
		d.set_speed_sp(100);
		a.set_speed_sp(100 - correction*10);
		}
		else if(correction < 0){
			d.set_speed_sp(100-correction*10);
			a.set_speed_sp(100);			
		}
		a.run_forever();
		d.run_forever();
		
}