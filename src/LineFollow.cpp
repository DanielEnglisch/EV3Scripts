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

color robot::boost(color in){
	int avg = (in.red + in.green + in.blue)/3;
	int fact = 2;

	if (in.red >= avg) in.red *=fact;
		else in.red /=fact;
	if (in.green>=avg) in.green *=fact;
			else in.green /=fact;
	if (in.blue>=avg) in.blue *=fact;
			else in.blue /=fact;
	fix(in);
	return in;
}

color robot::read_color_right(color_sensor & right_color, color const & cal){
	color temp;
	for (int i = 0; i < 11; ++i){
	temp.red   += std::get<0>(right_color.raw());
	temp.green += std::get<1>(right_color.raw());
	temp.blue  += std::get<2>(right_color.raw());
	}
	temp.red /=10;
	temp.green /=10;
	temp.blue /=10;
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

	void robot::go_straight(int pos, int speed, motor & m_right, motor &m_left){
		int pos_l = m_left.position();
		int pos_r = m_right.position();
		
		m_left.set_position_sp(-pos);
		m_right.set_position_sp(-pos);
		m_left.set_speed_sp(-speed);
		m_right.set_speed_sp(-speed);
		m_left.run_to_rel_pos();
		m_right.run_to_rel_pos();
		int counter(0);
		while(m_left.position() >= pos_l-pos && m_right.position() >= pos_r-pos) counter++;//  std::cout <<"POS-NOW: " << m_left.position() << " pos_target:" <<pos_l-pos << std::endl;
		//
	}

	void robot::turn(int degrees, motor & m_right, motor & m_left){
		go_straight(325,500,m_right,m_left);

		//turn left 90
		int pos_l = m_left.position();
		int pos_r = m_right.position();
		int pos  = 400;

		m_left.set_position_sp(pos);
		m_right.set_position_sp(-pos);
	
		m_left.set_speed_sp(500);
		m_right.set_speed_sp(-500);
		
		m_left.run_to_rel_pos();
		m_right.run_to_rel_pos();
		int counter(0);
		std::cout <<"POS-NOW: " << m_left.position() << " pos_target:" <<pos_l-pos << std::endl;
		while(m_left.position() <= pos_l+pos && m_right.position() >= pos_r-pos) std::cout <<"POS-NOW: " << m_left.position() << " pos_target:" <<pos_l+pos << std::endl;
	}



bool robot::is_in(color const & in){
	for(color x: recipe){
		if(is_color_equal(x,in,deviation)){
			x = {-1,-1,-1};
			return true;
		}
	}
	return false;
}

void robot::get_stones(){
	
	int speed(200);
	color temp = {0,0,0};
	short escape = 1;
	double val;
	float throttle;
	
	
	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);	

	light_sensor line_sensor (INPUT_2);
	line_sensor.set_mode(light_sensor::mode_reflect);

	color_sensor right_color (INPUT_3);
	right_color.set_mode(color_sensor::mode_col_color);

	color cal = temp;//read_color_right(right_color, temp);

	while(button::back.pressed()){
	
		if(is_color_right(right_color, cal)){ // && (temp.red + temp.green + temp.blue) < 300

			temp = read_color_right(right_color, {-30,80,0});
			fix(temp);	
			if (!is_in(temp)) go_straight(200,speed,m_right,m_left);
			else{ 	
					// turn left 90
					// go until stone
					// grab stone
					// turn 180
					// go until stone
					// turn left 90
					// go until stone(box)
				turn(90, m_right,m_left);
				go_straight(200,speed,m_right,m_left);
				grab_stone();
				turn(180,m_right, m_left);
				go_straight(200,speed,m_right,m_left);
				turn(90,m_right, m_left);
				go_straight(200,speed,m_right,m_left);
			}
		}		
	 }
		steer(line_sensor.value(),m_left,m_right,speed);
		m_right.run_forever();
		m_left.run_forever();
		escape = button::back.pressed();
}

void robot::save_recipe(){
	std::ofstream  out("/var/www/html/in.txt");
	if(out.good()){
	out << recipe.size() << std::endl;
	for(color x:recipe) out << x.red << ';' << x.green << ';' << x.blue << std::endl;	
	//	for(int i = 0; i < recipe.size(); ++i) out << recipe[i].red << ';'<< recipe[i].green << ';'<< recipe[i].blue << ';'<< std::endl;
	}
	out.close();
}

void robot::read_recepie(){
	int speed(200);
	color temp;
	short escape = 1;
	double val;
	float throttle;
	
	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);

	light_sensor line_sensor (INPUT_2);
	line_sensor.set_mode(light_sensor::mode_reflect);

	color_sensor right_color (INPUT_3);
	right_color.set_mode(color_sensor::mode_col_color);

	temp.red = 0; temp.green = 0; temp.blue =0;
	recipe_t rezept;
	color cal = temp;//read_color_right(right_color, temp);

	std::cout << "CALIBRATION: " << cal.red <<';'<< cal.green <<';'<< cal.blue <<std::endl;
	// while(button::back.pressed()){
	
	while(button::back.pressed() || (escape != 0) ){
		color brick = {255,255,255};
		
		//std::cout << read_color_right(right_color, cal).red << ';' << std::endl;
		if(
			is_color_right(right_color, cal) && 
			!is_color_equal(read_color_right(right_color, {-30,80,0}),temp, 90)  //&& 
			){ // && (temp.red + temp.green + temp.blue) < 300
		escape = 2;
		//if(is_color_right(right_color,cal)){ // temp = white || temp =={0,0,0}
			brick = temp;
			temp = read_color_right(right_color, {-30,80,0});
			fix(temp);
			
			if(is_color_equal(brick,{255,255,255},deviation) && !is_color_equal(temp,{255,255,255},deviation)){

			std::cout << "NOT WIHITE!" << std::endl;
			rezept.push_back(boost(temp));

			std::cout << temp.red << ';'<< temp.green << ';'<< temp.blue  << ';'<< std::endl;
			std::cout << "\x1b[38;2;"<< temp.red << ';'<< temp.green << ';'<< temp.blue <<  "m█████\n█████\n█████\x1b[0m" << std::endl;
		
		}

			
		 }
		 else if(!is_color_right(right_color, cal) && escape == 2){
				std::cout << "NOSTONE" << std::endl;
  				 escape = 0;
		 }
		steer(line_sensor.value(),m_left,m_right,200);
		m_right.run_forever();
		m_left.run_forever();
		escape = button::back.pressed();
	}

	m_right.stop();
	m_left.stop();
	std::cout << "CAL-Color:"  << cal.red << ';' << cal.green << ';' << cal.blue << std::endl;
	for(color x:rezept) std::cout << x.red << ';'<< x.green <<';' << x.blue << std::endl;
	recipe = rezept;
	save_recipe();
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
