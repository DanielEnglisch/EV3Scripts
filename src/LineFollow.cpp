#include "LineFollow.h"




// bool robot::stone_front(infrared_sensor &input){return false;}											//TODO: is stone in front of arms
// void robot::turn_180(tank_functions &input){};												//TODO: turns the robot around
// void robot::turn_right(tank_functions &input){};												//TODO: turns the robot right by 90deg
// void robot::turn_left(tank_functions &input){};
// bool robot::get_stone(){return false;}
// bool robot::drop_stone(){return false;}



bool robot::is_color_right(color_sensor & right_color, color const &cal) {
	return (	
	(std::get<0>(right_color.raw())-cal.red) + 
	(std::get<1>(right_color.raw())-cal.green) +
	(std::get<2>(right_color.raw())-cal.blue)
	) > 9;
}

color robot::read_color_right(color_sensor & right_color, color const & cal){
	color temp;
	temp.red   = std::get<0>(right_color.raw());
	temp.green = std::get<1>(right_color.raw());
	temp.blue  = std::get<2>(right_color.raw());
	return temp;
}

bool robot::is_color_equal(color const &in1, color const &in2,int deviation){
	return abs(in1.red-in2.red)<deviation &&
	abs(in1.green-in2.green)<deviation && 
	abs(in1.blue-in2.blue)<deviation;
}
void robot::fix(color &in){
	if (in.red > 255) in.red = 255;
	else if (in.red <0) in.red = 0;
	if (in.green > 255) in.green = 255;
	else if (in.green <0) in.green = 0;
	if (in.blue > 255) in.blue = 255;
	else if (in.blue <0) in.blue = 0;
}

void robot::read_recepie(){
	int speed(200);
	color temp;
	bool escape = false;
	double val;
	float throttle;
	
	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);

	light_sensor line_sensor (INPUT_2);
	line_sensor.set_mode(light_sensor::mode_reflect);

	color_sensor right_color (INPUT_3);
	right_color.set_mode(color_sensor::mode_col_color);

	temp.red = 0; temp.green = 0; temp.blue =0;
	recepie rezept;
	color cal = read_color_right(right_color, temp);
	//std::cout << "CAL" << cal.red <<';'<< cal.green <<';'<< cal.blue <<std::endl;
	// while(button::back.pressed()){
		cal = {-35,0,0};
	while(button::back.pressed()){
		color brick;
		//std::cout << read_color_right(right_color, cal).red << ';' << std::endl;
		if(is_color_right(right_color, cal) && !is_color_equal(read_color_right(right_color, cal),temp, 20) ){ // && (temp.red + temp.green + temp.blue) < 300
		//if(is_color_right(right_color, cal) && color){ // temp = white || temp =={0,0,0}
			temp = read_color_right(right_color, cal);
			fix(temp);
			rezept.push_back(temp);

			std::cout << temp.red << ';'<< temp.green << ';'<< temp.blue  << ';'<< std::endl;
			std::cout << "\x1b[38;2;"<< temp.red << ';'<< temp.green << ';'<< temp.blue <<  "m########\x1b[0m" << std::endl;
		 	//steer(line_sensor.value(),m_right, m_left, speed);
	 			// m_right.set_position_sp(-200);
				// m_left.set_position_sp(-200);

				// int count(0);
				// int actual_l = m_left.position_sp()-200;	
				// int actual_r = m_right.position_sp()-200;	
				// m_right.run_to_rel_pos();
				// m_left.run_to_rel_pos();

			//	while (m_right.position_sp()-50 > actual_r ||m_left.position_sp()-50> actual_l)count++;
			//std::cout << temp.red << ';' << temp.green << ';'<< temp.blue << std::endl;

		} // stop and wait 500 ms
		
		steer(line_sensor.value(),m_right,m_left, speed);
		m_right.run_forever();
		m_left.run_forever();
		
		escape = button::back.pressed();
	}
	m_right.stop();
	m_left.stop();
	std::cout << "CAL-Color:"  << cal.red << ';' << cal.green << ';' << cal.blue << std::endl;
	for(color x:rezept) std::cout << x.red << ';'<< x.green <<';' << x.blue << std::endl;
}


void robot::follow_line_d(){
	bool escape = false;
	double val;
	float throttle;
	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);
	light_sensor line_sensor (INPUT_2);

	while(button::back.pressed()){
		steer(line_sensor.value(),m_left, m_right,1000);
		m_right.run_forever();
		m_left.run_forever();
	}
	m_right.stop();
	m_left.stop();
}


void robot::steer(int light_val, motor & m_left, motor & m_right, int throttle) {
	float smoothing_factor=0.5;
	float steering = floatMap(light_val,350,600,0,1);
	float speed_right = 1-steering;
	float speed_left = steering;
	speed_right = floatMap(speed_right, 0,1,0,100 );
	speed_left = floatMap(speed_left, 0,1,0,100 );
	
	speed_right *=smoothing_factor;
	speed_left *=smoothing_factor;
	
	if( speed_right >100) speed_right =100;
	if(speed_right < 0) speed_right =0;
	if(speed_left < 0) speed_left =0;
	if( speed_left >100) speed_left =100;
	
	speed_right = throttle * (speed_right/100); // abbild von den 
	speed_left = throttle * (speed_left/100);
	//std::cout<< speed_left << ';' << speed_right << std::endl;
	m_right.set_speed_sp(-speed_right);
	m_left.set_speed_sp(-speed_left);
}


float robot::floatMap(float vx, float v1, float v2, float n1, float n2){
	//this function maps vx in the range v1 to v2 to the new range n1 and n2
    // v1 start of range, v2 end of range, vx the starting number between the range
    float percentage = (vx-v1)/(v2-v1);
    // n1 start of new range, n2 end of new range
    return (n2-n1)*percentage+n1;
}



void robot::forward_motors(float correction){
	motor a(OUTPUT_A);
	motor d(OUTPUT_D);
	correction *= 10;
	
	if(correction > 0) {
		d.set_speed_sp(100);
		a.set_speed_sp(-100);
	}
	else if(correction < 0){
		d.set_speed_sp(-100);
		a.set_speed_sp(100);			
	}
	else if(correction == 0) {
		d.set_speed_sp(-100);
		a.set_speed_sp(-100);

	}
		a.run_forever();
		d.run_forever();


	int counter(0);
		 	int time_start(time(0));
		 	while(time_start+6.25 >= time(0))counter++;
			
		a.stop();
		d.stop();
		
}
