#include "LineFollow.h"


bool robot::stone_front(infrared_sensor &input){return false;}											//TODO: is stone in front of arms
void robot::turn_180(tank_functions &input){};												//TODO: turns the robot around
void robot::turn_right(tank_functions &input){};												//TODO: turns the robot right by 90deg
void robot::turn_left(tank_functions &input){};
bool robot::get_stone(){return false;}
bool robot::drop_stone(){return false;}

color robot::read_color_right(color_sensor &input, float deviation, recepie &input2) {
	float	temp_input = input.value();
	return robot::convert_color(temp_input, deviation,input2);
	
}
color robot::read_color_down(light_sensor &input, float deviation) {
	float	temp_input = input.value();
	recepie a;
	robot::convert_color(temp_input, deviation, a);
}


color robot::convert_color(float value, float deviation, recepie &input2) {
	if		((red_cl - deviation) > value &&	(red_cl + deviation) < value) {		++input2.red; return red; }
	else if ((green_cl - deviation) > value &&	(green_cl + deviation) < value) {	++input2.green; return green; }
	else if ((blue_cl - deviation) > value &&	(blue_cl + deviation) < value) {	++input2.blue; return blue; }
	else if ((yellow_cl - deviation) > value && (yellow_cl + deviation) < value) {	++input2.yellow; return yellow; }
	else if ((black_cl - deviation) > value &&	(black_cl + deviation) < value) {	++input2.black; return black; }
	else { ++input2.error; return error; }
}

bool robot::is_color_right(color_sensor &input) {
	return	(input.value() > 0 && input.value() < 100);	//true if color value is between 0 and 100
}


recepie robot::read_recepie(float deviation) {

	color_sensor c(INPUT_3);							//initialize color sensor -> side
	light_sensor s(INPUT_2);							//initialize color sensor -> down
	motor a(OUTPUT_D);									//left motor
	motor b(OUTPUT_A);									//right motor

	c.set_mode(color_sensor::mode_col_reflect);
	s.set_mode(light_sensor::mode_reflect);				//init color sensor right

	recepie help;
	double val(0);
	float throttle(0.05);

	while (!button::back.pressed())
	{
		if (!is_color_right(c)) {
			val = s.value();
			drive(val, throttle, 1, a, b);
			a.run_forever();
			b.run_forever();
		}
		else {
			read_color_right(c,deviation,help);
		}
	}
	a.stop();
	b.stop();
	return help;
}
bool robot::is_in(recepie &input, color input2) {
	switch (input2) {
	case error:
		std::cout << "ERROR!";
		return false;
		break;
	case red:
		if (input.red > 0) { --input.red; return true; }
		break;
	case green:
		if (input.green > 0) { --input.green; return true; }
		break;
	case blue:
		if (input.blue > 0) { --input.blue; return true; }
		break;
	case yellow:
		if (input.yellow > 0) { --input.yellow; return true; }
		break;
	case black:
		if (input.black > 0) { --input.black; return true; }
		break;
	default:
		std::cout << error;
		return false;
	}
}

bool robot::collect_stones(recepie &stones, float deviation){
	color_sensor c(INPUT_3);																//initialize color sensor -> side
	light_sensor s(INPUT_2);																//initialize color sensor -> down
	motor a(OUTPUT_D);																		//left motor
	motor b(OUTPUT_A);																		//right motor
		
	c.set_mode(color_sensor::mode_col_reflect);
	s.set_mode(light_sensor::mode_reflect);													//init color sensor right
	double val(0);
	float throttle(0.05);
	tank_functions input_tank = {a,b,s,0.5,throttle};
	while (!button::back.pressed())															//STOP IF ESCAPE IS PRESSEND
	{
		if (!is_color_right(c)) {															//FOLLOW LINE AS LONG AS NO STONE IS ON RIGHT
			val = s.value();																
			drive(val, throttle, 1, a, b);
			a.run_forever();
			b.run_forever();
		}
		else {
			color temp_col = read_color_right(c, deviation,stones);							//READ BRICK COLOR
			if (is_in(stones, temp_col)) {													//IS BRICK COLOR STILL IN RECEPIE
					
				back_sec(a,b,1,2000);														//GO BACK STRAIGT NO LINE FOLLOW 2000ms
				turn_left(input_tank);														//GO LEFT
																			
				infrared_sensor input;														//INIT IR-SENSOR FRONT create infrared input
				input.set_mode("mode_us_si_cm");											//INIT IR-SENSOR FRONT set mode to single reading in cm
				robot::go_until(input_tank, input);											//GO ON STORAGE LINE UNTIL STONE IS FOUND
				get_stone();																//GRAB STONE
				turn_180(input_tank);														//TURN AROUND
				robot::go_until(input_tank, input);											//GO TO END OF STORAGE LINE
				turn_left(input_tank);														//GO LEFT
				robot::go_until(input_tank, input);											//GO TO END											as long as no stone is found go straigt TODO: test if a ( go until line ends) algorithm is better to detect 'Mixing' area (if go_until works with functions just make a new 'trigger')
				drop_stone();																//DROP STONE
				turn_180(input_tank);														//TURN AROUND
				robot::go_until(input_tank, input);											//GO TO BEGINNING									TODO: find better algorithm to detect robot is at the end (if go_until works with functions just make a new 'trigger')
				turn_180(input_tank);														//TURN AROUND
			}
			else {	
				back_sec(a, b, -1, 1000);													//if stone is not in recepie go straigt forward 1 second TODO: Check: maybe line following better?
			}
		}
	}
	a.stop();
	b.stop();

	return stones.error == 0;
}

void robot::go_until(tank_functions &input,infrared_sensor &input2) {						 //, depends f
	float val(0);
	while (!stone_front(input2)) {															//as long as no stone is found go straigt
		val = input.s.value();
		drive(val, input.speed, 1, input.a, input.b);
		input.a.run_forever();
		input.b.run_forever();
	}
}



void robot::back_sec(motor &a, motor &b, float throttle, float time) {						
	while (!button::back.pressed()){
		robot::drive(1, -throttle, 1, a, b);
			a.set_time_sp(time);
			b.set_time_sp(time);
			a.run_timed();
			b.run_timed();
		}
	a.stop();
	b.stop();
}


void robot::follow_line_d(){
	motor a (OUTPUT_D);																		//Init motor a 
	motor b (OUTPUT_A);																		//Init motor b 
	light_sensor s (INPUT_2);																//Init lightsensor s 
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

void robot::drive(float steering, float throttle,int mode, motor a, motor b){
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
	
	cout << "motA: " << motA << endl;
	cout << "motB: " << motB << endl;

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

float robot::floatMap(float vx, float v1, float v2, float n1, float n2){//this function maps vx in the range v1 to v2 to the new range n1 and n2
	
    // v1 start of range, v2 end of range, vx the starting number between the range
    float percentage = (vx-v1)/(v2-v1);
    // n1 start of new range, n2 end of new range
    return (n2-n1)*percentage+n1;
}

void  robot::calibrate(){
	float white = 40;
	float black = 30;
}

void robot::forward_motors(float correction){
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