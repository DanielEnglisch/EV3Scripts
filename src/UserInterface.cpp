#include "UserInterface.h"

void UserInterface::buttonTest(){
	while(button::back.pressed()){
		std::cout << "NOT PRESSED" << std::endl;
	}
}