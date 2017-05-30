#if !defined UI_H
#define UI_H
	
	#include "ev3dev.h"
	#include <iostream>
	using namespace ev3dev;	
	using namespace std;

	class UserInterface
	{
		public:
			static void prompt(const string &str1);
			static void beep();
			
	};
#endif
