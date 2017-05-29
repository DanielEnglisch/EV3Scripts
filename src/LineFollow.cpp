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
	) > 20;
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
//	for (int i = 0; i < 5; ++i){
	temp.red   = std::get<0>(right_color.raw());
	temp.green = std::get<1>(right_color.raw());
	temp.blue  = std::get<2>(right_color.raw());
	temp.red -= cal.red;
	temp.red -= cal.green;
	temp.blue -= cal.blue;

//	}
	// temp.red /=5;
	// temp.green /=5;
	// temp.blue /=5;
	fix(temp);
	return temp;
}

bool robot::is_color_equal(color const &in1, color const &in2,int deviation){
	//std::cout <<abs(in1.red-in2.red) << ';'<<abs(in1.green-in2.green) << ';'<<abs(in1.blue-in2.blue) << std::endl;
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

void robot::turn(int degrees, motor & m_right, motor & m_left, bool stone){
		int pos(0);
		if (degrees == 90){
			if (stone)go_straight(450,500,m_right,m_left);
			pos  = 320;
		}
		if (degrees ==180){
			pos  = 750;
		}
		if(degrees ==45){
			go_straight(-200,500,m_right,m_left);
			pos = 200;
			
		}
		else std::cout << "NIX";
	
		//turn left 90
		int pos_l = m_left.position();
		int pos_r = m_right.position();
		
		m_left.set_position_sp(pos);
		m_right.set_position_sp(-pos);
	
		m_left.set_speed_sp(500);
		m_right.set_speed_sp(-500);
		
		m_left.run_to_rel_pos();
		m_right.run_to_rel_pos();
		int counter(0);
		while(m_left.position() <= pos_l+pos && m_right.position() >= pos_r-pos) ++counter;
		if(degrees == 45){
			go_straight(220,500,m_right,m_left);
		}

}
bool robot::is_in(color const & in){
	for(int i= 0; i < recipe.size(); ++i){
		//std::cout << "\x1b[38;2;"<< x.red << ';'<< x.green << ';'<< x.blue <<  "m█████\x1b[0m" << "\x1b[38;2;"<< in.red << ';'<< in.green << ';'<< in.blue <<  "m█████\x1b[0m"<< std::endl;
		if( (recipe[i].red != -1 && recipe[i].green != -1  && recipe[i].blue != -1 ) && is_color_equal(recipe[i],in,40)){
		//	std::cout << "ISIN! :" << x.red << ';' << x.green << ';'<< x.blue  << ';'<< std::endl;
			recipe[i] = {-1,-1,-1};
			return true;
		}
	}
	return false;
}

void robot::follow_line_until_stone(int speed, motor & m_right, motor & m_left,light_sensor & line_sensor,infrared_sensor & ir, bool to_bucket){
	
	int distance(0);
	bool exit = true;
	
	color_sensor right_color (INPUT_3);
	right_color.set_mode(color_sensor::mode_col_color);
	
	int start(0);
	for(int i = 1; i < 30;++i) start +=ir.value(false);
	start /=30;
	start= ir.value();	
	std::cout << "START: "<< start<<std::endl;
	while (button::back.pressed() &&( 
				distance == 0 || (
				ir.value(false) >= (start*0.2) // jetziger wert 10% kleiner als vorgehender
				)) && exit){
				
					if((m_left.speed() + m_right.speed()) >= 0 && corner_stones == 0 && to_bucket) exit = false;
				if(to_bucket && is_color_right(right_color,{19,6,0})){
					if((m_left.speed() + m_right.speed()) < 0 )  ++corner_stones;
					if((m_left.speed() + m_right.speed()) >= 0 )  --corner_stones;
				}
				std::cout << ir.value()<< std::endl;
				distance = ir.value(false);
				steer(line_sensor.value(),m_left, m_right,500);
				m_right.run_forever();
				m_left.run_forever();
			}
			
	m_right.stop();
	m_left.stop();
}

// void robot::drop_to_mixer(int speed, motor & m_right, motor & m_left,light_sensor & line_sensor,infrared_sensor & ir){
// }
void robot::wait(){
			int counter(0);
		 	double time_start(time(0));
		 	while(time_start+0.2 >= time(0))counter++;
			// return counter;
}

void robot::get_stones(){
	int speed(400);
	color temp = {0,0,0};

	short escape = 1;
	color last_col = temp;
	infrared_sensor ir(INPUT_1);
	ir.set_mode(infrared_sensor::mode_ir_prox);

	read_recipe_file();

	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);
	light_sensor line_sensor (INPUT_2);
	line_sensor.set_mode(light_sensor::mode_reflect);

	color_sensor right_color (INPUT_3);
	right_color.set_mode(color_sensor::mode_col_color);

	color cal = temp;//read_color_right(right_color, temp);
	Claw x;

	while(button::back.pressed()  && (escape != 0) ){
		
		if(is_color_right(right_color, cal)){ // && (temp.red + temp.green + temp.blue) < 300
			temp = read_color_right(right_color, {19,6,0});
			//std::cout << " IS IN: " << "\x1b[38;2;"<< temp.red << ';'<< temp.green << ';'<< temp.blue <<  "m█████\n█████\n█████\x1b[0m" << std::endl;
			if(is_in(temp) && !is_color_equal(temp,last_col,deviation)){
					for(color x : recipe) std::cout  << " IS IN: " << "\x1b[38;2;"<< x.red << ';'<< x.green << ';'<< x.blue <<  "m█████\n█████\n█████\x1b[0m" << std::endl;
					turn(90, m_right,m_left);
					follow_line_until_stone(speed,m_right,m_left,line_sensor, ir);
						x.lower();
						x.close();
						x.wait();
						x.lift();
				turn(180, m_right,m_left);
				follow_line_until_stone(speed,m_right,m_left,line_sensor, ir);
				turn(45, m_right,m_left,false);
				follow_line_until_stone(speed,m_right,m_left,line_sensor, ir,true);
				x.half_lower();
				x.wait();
				
				m_left.stop();
				m_right.stop();
				x.wait();x.wait();
				speed =0;
				escape =0;
			 	x.open();
			 	last_col = temp;
			} 
		}
		// 	if (!is_in(temp)) go_straight(200,speed,m_right,m_left);
		// 	else{
		// 		turn(90, m_right,m_left);
		// 		follow_line_until_stone(speed,m_right,m_left,line_sensor, ir);
		// 			x.lower();
		// 			x.close();
		// 			x.wait();
		// 			x.lift();
		// 			escape = 0;
				
		// 		// turn(90, m_right,m_left);
		// 		// turn(90, m_right,m_left);

		// 		// follow_line_until_stone(speed,m_right,m_left,line_sensor,ir);
		// 		// turn(90, m_right,m_left);
		// 		// follow_line_until_stone(speed,m_right,m_left,line_sensor,ir);
		// 		// 	x.half_lower();
		// 		// 	x.open();
		// 		// 	x.wait(); x.wait();
		// 		// 	x.close();x.lift();
		// 		// turn(90,m_right, m_left);
		// 		// turn(90,m_right, m_left);
		// 		// go_straight(200,speed,m_right,m_left);
		// 	}
		// }		
	
		
		
		steer(line_sensor.value(),m_left,m_right,speed);
		m_right.run_forever();
		m_left.run_forever();
 }
		m_right.stop();
		m_left.stop();
}

void robot::save_recipe(){
std::ofstream  out("/var/www/html/in.txt");
	if(out.good()){
		for(color x:recipe){
		//	boost(x);
			//std::cout << x.red << ';' << x.green << ';' << x.blue << std::endl;	
			out << x.red << ';' << x.green << ';' << x.blue << std::endl;
		}
	}	
	//	for(int i = 0; i < recipe.size(); ++i) out << recipe[i].red << ';'<< recipe[i].green << ';'<< recipe[i].blue << ';'<< std::endl;
	out.close();
}

void robot::read_recipe_file(){
	std::ifstream  in("/var/www/html/in.txt");
	 recipe.clear();
	
	 std::string s;
	 char* temp = new char[12];
	 char* item;
	 int red;
	 int green;
	 int blue;

	 while(std::getline(in,s))
	 {
	 	for (int i = 0; i < s.size(); ++i)	
	 {
	 		temp[i] = s[i];
	 	}

	 	temp[s.size()] = '\0';

	 	item = strtok(temp,";");
	 	red = atoi(item);
	 	item = strtok(nullptr,";");
	 	green = atoi(item);
	 	item = strtok(nullptr,"\0");
	 	blue = atoi(item);


	 	recipe.push_back({red,green,blue});
	 }
	in.close();
	 delete[] temp; temp = nullptr;
	 for (color x : recipe){
	 	std::cout << x.red <<  " " << x.green <<  " " << x.blue <<  std::endl;
	 		 }
	//recipe = {{185,13,16},{248,134,51},{0,70,25}};
}

bool robot::grey(color const & in){	
	int devi(15);
	int avg = (in.red + in.green + in.blue)/3;

	return( avg >150 && 
		((in.red+devi) >= avg && (in.red -devi) <avg) &&
		((in.green+devi )>= avg && (in.green -devi) <avg) &&
		((in.blue+devi) >= avg && (in.green -devi) <avg)
		
	);	
	
}
void robot::read_recepie(){
	//std::cout << "BEGINNING"<< std::endl;
	recipe.clear();
	short escape = 1;
	color_sensor s (INPUT_3);
	s.set_mode(color_sensor::mode_col_color);
	color cal = {0,0,0};
	color last ={0,0,0};
	color last_real;
	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);

	light_sensor line_sensor (INPUT_2);
	line_sensor.set_mode(light_sensor::mode_reflect);
//std::cout << "middle_half"<< std::endl;
	while(button::back.pressed() && (escape != 0)){
		if(is_color_right(s,cal)){
			color x = (read_color_right(s,{19,6,0}));
			escape = 2;
			//std::cout << "MIDLLE-WHILE"<< std::endl;
			if((abs(x.red-last.red) < 3 && abs(x.green-last.green) < 3 && abs(x.blue-last.blue) < 3 ) &&
				(x.red > 20 || x.green >20 || x.blue > 20) && !grey(x)
				){
				if(!is_color_equal(x,{255,255,255},deviation) && !is_color_equal(x,last_real,deviation)){
				recipe.push_back(x);
			
				//std::cout << "\x1b[38;2;"<< x.red << ';'<< x.green << ';'<< x.blue <<  "m█████\n█████\n█████\x1b[0m" << std::endl;
				std::cout << x.red << ';'<< x.green << ';'<< x.blue << std::endl;
				last_real = x;
				}
			}
		// if((x.red + x.green + x.blue )>200 && !is_color_equal(x,last,deviation) && is_color_equal(last,{255,255,255},deviation) && !is_color_equal(x, {255,255,255},deviation)) { // not white
		// 		recipe.push_back(x);
		// 	}
		last=x;	
			
		}else if(!is_color_right(s,cal) && escape == 2){
 			escape = 0;
			m_left.stop();
			m_right.stop();
		}
		steer(line_sensor.value(),m_left, m_right,200);
		m_right.run_forever();
		m_left.run_forever();
	}
	//	std::cout << "END-WHILE"<< std::endl;
	m_right.stop();
	m_left.stop();
save_recipe();
rec_fin = true;
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


void robot::test(){
// for(int i = 0; i < 10; ++i) std::cout << i << ';' << i << ';'<< i << ';'<< std::endl;
// rec_fin = true;
	// color_sensor s (INPUT_3);
	// s.set_mode(color_sensor::mode_col_color);
	// color cal = {0,0,0};
	// read_recepie_file();
	// while(button::back.pressed()){
	// 	if(is_color_right(s,cal)){
	// 		for(color x : recipe) std::cout  << "\x1b[38;2;"<< x.red << ';'<< x.green << ';'<< x.blue <<  "m█████\n█████\n█████\x1b[0m" << std::endl;
	// 		color x = (read_color_right(s,cal));
	// 		if(is_in(x)) std::cout << " IS IN: ";
	// 	}
	// }

	// infrared_sensor ir(INPUT_1);
	// ir.set_mode(infrared_sensor::mode_ir_prox);
	// while(button::back.pressed()){
	// 	std::cout << ir.value()<< std::endl;
	// }

	infrared_sensor ir(INPUT_1);
	ir.set_mode(infrared_sensor::mode_ir_prox);

	motor m_right(OUTPUT_A);
	motor m_left(OUTPUT_D);

	light_sensor line_sensor (INPUT_2);
	line_sensor.set_mode(light_sensor::mode_reflect);


	follow_line_until_stone(200,m_right,m_left,line_sensor, ir);
	turn(45, m_right,m_left,false);
} 