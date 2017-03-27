#if !defined TESTING_H
#define TESTING_H

	#include <iostream>
	#include "ev3dev.h"
	//using ev3dev::motor;
	using namespace ev3dev;
	using std::cout; using std::endl;

	class LineFollow_testing{
		public:
			void vorprojekttag();
			void follow_line_new_pid();
			void follow_line_p();
	};

#endif