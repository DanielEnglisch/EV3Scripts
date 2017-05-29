#if !defined LINEFOLLOW_H
#define LINEFOLLOW_H
	
	#include "Claw.h"
	#include <iostream>
	#include "ev3dev.h"
	#include <vector>
	#include <cmath>				 //only std::abs used
	#include <tuple> 
	#include <string>
	#include <fstream>
	#include "Claw.h"
	using namespace ev3dev;			//using ev3dev::motor;

	using std::cout; using std::endl; using std::abs; using std::vector;
	
	#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));									
	
	struct color {
		int red;
		int green;
		int blue;
	};

	typedef						std::vector<color>  recipe_t;

	class robot
	{
		private:
			
			bool 			grey(color const & in);
			int		const	deviation = 60;
			int		const	deviation_ir = 10;
			void 			fix(color &in);
			color		 	boost(color in); 
			//void 			turn(int degrees);
			bool			is_in(color const & in);	
			void			go_straight(int pos, int speed, motor & m_right, motor &m_left);
			
			void			steer(int light_val, motor & m_left, motor & m_right, int throttle);
			float			floatMap(float vx, float v1, float v2, float n1, float n2);
			void			forward_motors(float correction);							
			bool			is_color_right(color_sensor & right_color, color const &cal);
			color			read_color_right(color_sensor & right_color, color const & cal);										//blue color level of right sensor
			bool			is_color_equal(color const &in1, color const &in2,int deviation);	
			void			save_recipe();	

		public:
				recipe_t 		recipe;
				int				corner_stones = 0;
				// ~robot(){
				// 	 motor r(OUTPUT_A);
				// 	 motor l(OUTPUT_D);
				// 	 r.stop();
				// 	 l.stop();
					 
				// }
				//robot	();
				// bool stone_front(infrared_sensor &input){return false;}			
				void			turn(int degrees, motor & m_right, motor & m_left, bool stone = true);	
				bool rec_fin = false;								//TODO: is stone in front of arms
				void test();
				void read_recepie_file();
				void follow_line_until_stone(int speed, motor & m_right, motor & m_left,light_sensor & line_sensor,infrared_sensor & ir, bool to_bucket = false);
				void get_stones();
				void read_recepie();
				void follow_line_d();
	};
#endif // LINEFOLLOW_H
