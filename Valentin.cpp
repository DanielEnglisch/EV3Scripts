#include "Valentin.h"
#include <iostream>
#include "ev3dev.h"
#include <unistd.h>
#include "math.h"

#define SEED_MULTIPLICATOR 1
#define SPEED 200


struct motor_speeds{
	int motora = 0;
	int motorb = 0;
	bool error = false;	
};

struct light_intens{
	int counter= 0;
	int avg= 0;
};

bool follow_line_original();
void drive_direction(motor * a, motor * d, double direction);
motor_speeds get_speed(light_sensor &s,light_intens &light,int roi_light=45, int roi_dark0=28,  int stop_level=45 ,int speed=1); //reflection_val == roi of light stuff (white floor) -> ~40
void follow_line_new_pid();

void test(){
	std::cout << "ANAL" << std::endl;
}

	
bool follow_line_original(){

	bool escape (false);
		light_sensor s(INPUT_2);
		s.set_mode(light_sensor::mode_reflect);
        //cout << s.reflected_light_intensity();
        motor d(OUTPUT_D);
        motor a(OUTPUT_A);
		motor_speeds help;
		light_intens light;
	
		while ( !escape ){
			
			//roi value of white area = 52.2
			//roi value of black area = 33.15
			help = get_speed(s,light,52.2/2,33.15,800,5);
			a.set_speed_sp(help.motora);
			d.set_speed_sp(help.motorb);

			a.run_forever();
			d.run_forever();
			
			
			 escape = button::back.pressed() || help.error;
			//usleep (100);
        }

		a.reset();
		d.reset();
     

return 0;
}




motor_speeds get_speed(light_sensor &s,light_intens &light,int roi_light, int roi_dark, int stop_level ,int speed){
	motor_speeds help;
	float b_speed = s.reflected_light_intensity();
		light.avg += b_speed;
		++light.counter;
		cout << b_speed << endl;
	help.error = (light.counter >= 10  && (light.avg/10) >= stop_level);
				if(help.error)cout <<  "ERORROR"<< b_speed << endl;
		if(light.counter >= 10){ light.counter = 0; light.avg =0;}
	//cout << b_speed << endl;
	help.motorb =(roi_light-b_speed)*-speed;
	help.motora =(b_speed-roi_dark)*-speed;
	return help;
}



void follow_line_new_pid(){
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
	
	double kp = 5; //how sharp or smooth corretctions are
	double ki = 0.001; //test
	double kd = 0.001; //test
	double integra = 1;
	bool escape = false;
	double last_error(0);
	int base_speed(SPEED);
	double speed_a =0;
	double speed_b = 0;
	while ( !escape ){
		

	//correction =(error*KP)+(integral*Ki)+ derivative*kd;
	
		double sensor_value = s.reflected_light_intensity();
		double error = target_light_value - sensor_value;
		double output_a = (error)*kp;
		integra += error;
		double output_b  = integra*ki;
		double derivative = error - last_error;
		double output_c = derivative*kd;
		double direction = output_a+output_b+output_c;
		std::cout << output_a <<  ';' << output_b << ';' << output_c << '#' << direction << std::endl;
		//std::cout << sensor_value << std::endl;
		
		if(direction == 0){
			speed_a = SPEED;
			speed_b = SPEED;
		}else if(direction > 0){
			speed_a = SPEED + direction;
			speed_b = SPEED  - direction;
		}else if(direction < 0){
			speed_a = SPEED + direction;
			speed_b = SPEED - direction;			
		
		}
			
			
			d.set_speed_sp(speed_b);
			a.set_speed_sp(speed_a);
		
		
		
		a.run_forever();
		d.run_forever();
		
		escape = button::back.pressed();
		last_error=error;
		}	

		a.reset();
		d.reset();
     
}

void drive_direction(motor * a, motor * d, double direction){
	
}