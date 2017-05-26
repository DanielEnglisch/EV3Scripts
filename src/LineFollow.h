#if !defined LINEFOLLOW_H
#define LINEFOLLOW_H
	
	#include <iostream>
	#include "ev3dev.h"
	#include <vector>
	#include <cmath>				 //only std::abs used
	#include <tuple> 
	#include <string>
	using namespace ev3dev;			//using ev3dev::motor;

	using std::cout; using std::endl; using std::abs; using std::vector;
	
	#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));									
	
	struct color {
		int red;
		int green;
		int blue;
	};

	//typedef					void(*action)		(recepie &, float, float);									
	//typedef						bool(*depends)		(infrared_sensor &);												//TODO:  'depends'(trigger) function to work, to be able to use different triggers on a drive straigt function
	typedef						std::vector<color>  recepie;

	class robot
	{
		private:
			float			yellow_cl = 0;																				//yellow color level of right sensor
			float			green_cl = 5;																				//green color level of right sensor																			
			float			red_cl = 10;																					//red color level of right sensor
			float			black_cl = 0;																				//black color level of right sensor
			float			blue_cl = 2;	
			void 			fix(color &in);
			color		 	boost(color in); 																					//blue color level of right sensor
		public:
			//robot	();




				// bool stone_front(infrared_sensor &input){return false;}											//TODO: is stone in front of arms
				// void turn_180(tank_functions &input){};												//TODO: turns the robot around
				// void turn_right(tank_functions &input){};												//TODO: turns the robot right by 90deg
				// void turn_left(tank_functions &input){};
				// bool get_stone(){return false;}
				// bool drop_stone(){return false;}



				bool is_color_right(color_sensor & right_color, color const &cal);
				color read_color_right(color_sensor & right_color, color const & cal);
				bool is_color_equal(color const &in1, color const &in2,int deviation);
				void read_recepie();
				void follow_line_d();
				void steer(int light_val, motor & m_left, motor & m_right, int throttle);
				float floatMap(float vx, float v1, float v2, float n1, float n2);
				void forward_motors(float correction);


		
	};
#endif // LINEFOLLOW_H
