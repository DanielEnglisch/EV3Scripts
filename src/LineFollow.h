#if !defined LINEFOLLOW_H
#define LINEFOLLOW_H
	
	#include <iostream>
	#include "ev3dev.h"
	#include <vector>
	#include <cmath>        // std::abs
	
	using namespace ev3dev; //using ev3dev::motor;
	using std::cout; using std::endl; using std::abs; using std::vector;
	
	#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt));

	enum color {
		error,
		red,
		green,
		blue,
		yellow,
		black,
	};


	/*typedef					vector <color>		recepie;*/
	//typedef					void(*action)		(recepie &, float, float);
	//typedef					void(*depends)		(value_t &);
	struct recepie {
		std::size_t error = 0;
		std::size_t red = 0;
		std::size_t green = 0;
		std::size_t blue = 0;
		std::size_t yellow = 0;
		std::size_t black = 0;
	};

	class robot
	{

		public:

			bool			drop_stone			();
			bool			get_stone			();
			bool			is_in				(recepie &input, color input2);
			color 			convert_color		(float value, float deviation, recepie &input2);
			void			back_sec			(motor &a, motor &b, float throttle,float time);
//			void			follow_untildo		();															//possible Trigger function & action function
			bool			stone_front			(infrared_sensor &input);
			void			turn_180			(motor &a, motor &b, float speed);
			void			turn_right			(motor &a, motor &b, float curve, float speed);
			void			turn_left			(motor &a, motor &b, float curve, float speed);
			bool			collect_stones		(recepie &stones,float deviation);
			color 			read_color_right	(color_sensor &input,float deviation, recepie &input2);
			color			read_color_down		(light_sensor &input,float deviation);
			bool			is_color_right		(color_sensor &input);
			recepie			read_recepie		(float deviation);
			void			follow_line_d		();
			void			forward_motors		(float correction);
			void			calibrate			();
			float			floatMap			(float vx, float v1, float v2, float n1, float n2);
			void			drive				(float steering, float throttle, int mode, motor a, motor b);
			
		private:

			float			yellow_cl = 0;		// yellow color level
			float			green_cl = 0;
			float			red_cl = 0;
			float			black_cl = 0;
			float			blue_cl = 0;
	};
#endif // LINEFOLLOW_H
