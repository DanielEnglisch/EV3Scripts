#include "UserInterface.h"

void UserInterface::prompt(const string &str1){
	lcd l;
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');
	l.fill('X');

	cout << "String: " << str1 << endl;
}

void UserInterface::beep(){
	sound::beep();
}
