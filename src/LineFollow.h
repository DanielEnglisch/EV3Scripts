#if !defined LINEFOLLOW_H
#define LINEFOLLOW_H
	
	#include <iostream>
	#include "ev3dev.h"
	#include <vector>
	#include <cmath>				 //only std::abs used
	#include <tuple> 
	using namespace ev3dev;			//using ev3dev::motor;
	using std::cout; using std::endl; using std::abs; using std::vector;
	
	#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));									
	
	struct color {
		size_t red;
		size_t green;
		size_t blue;

	};

	//typedef					void(*action)		(recepie &, float, float);									
	//typedef						bool(*depends)		(infrared_sensor &);												//TODO:  'depends'(trigger) function to work, to be able to use different triggers on a drive straigt function
	typedef						std::vector<color>  recepie;
	struct tank_functions {																								//vital tank functions for functions
		motor &a;
		motor &b;
		light_sensor &s;
		float curve;
		float speed;
	};


	class robot
	{

		public:
			void 			test				(int light_val, float throttle, motor right, motor left);
			void 			read_recepie		();
			color 			read_color_right	(color_sensor &input, color const &cal);													//read the color from right sensor	
			bool 			is_color_equal		(color const &in1, color const &in2,int deviation);
			void			go_until			(tank_functions & input,infrared_sensor &input2);						//go until (currently until stone is infront) TODO: go until 'depends' (trigger) function is true 
			bool			drop_stone			();																		//TODO: drop a stone currently placeholder
			bool			get_stone			();																		//TODO: grab a stone from floor currently placeholder
			bool			is_in				(recepie &input, color input2);											//is current color in the recepie if yes -> subtract 1 form recepie
			color 			convert_color		(float value, float deviation, recepie &input2);						//convert raw color vals to colors better than original algorithm
			void			back_sec			(motor &a, motor &b, float throttle,float time);						//go back straigt for time sec
//			void			follow_untildo		();																		//possible Trigger function & action function
			bool			stone_front			(infrared_sensor &input);												//TODO: is stone in front of arms
			void			turn_180			(tank_functions &input);												//TODO: turns the robot around
			void			turn_right			(tank_functions &input);												//TODO: turns the robot right by 90deg
			void			turn_left			(tank_functions &input);												//TODO: turns the robot left by 90deg
			bool			collect_stones		(recepie &stones,float deviation);										//main algorithm collect all stones
		
			color			read_color_down		(light_sensor &input,float deviation);									//read the color from line-tracking refl sensor
			bool			is_color_right		(color_sensor &input, color const &cal);													//checks if stone is in front of the right color sensor
			//recepie			read_recepie		(float deviation);														//main pre-function goes along a line and returns a recepie
			void			follow_line_d		();																		//follows a line
			void			forward_motors		(float correction);														//go forward with both motors
			void			calibrate			();																		//calibrate rfl values of floor and line
			float			floatMap			(float vx, float v1, float v2, float n1, float n2);						//convert steering vals
			void			drive				(float steering, float throttle, int mode, motor a, motor b);			//tank-drive algorithm


		private:
			float			yellow_cl = 0;																				//yellow color level of right sensor
			float			green_cl = 5;																				//green color level of right sensor																			
			float			red_cl = 10;																					//red color level of right sensor
			float			black_cl = 0;																				//black color level of right sensor
			float			blue_cl = 2;																				//blue color level of right sensor
	};
#endif // LINEFOLLOW_H
