#include "UserInterface.h"

void UserInterface::buttonTest(){
	while(true){
		std::cout << button::back.pressed() << std::endl;
	}
}
