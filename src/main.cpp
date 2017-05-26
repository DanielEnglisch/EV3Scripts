//#include "support/SensorDebug.h"
#include "LineFollow.h"
//#include "UserInterface.h"

int main(){
	robot r;

	motor m_left(OUTPUT_A);
	motor m_right(OUTPUT_D);
	r.turn(0,m_left, m_right);
	
	//r.follow_line_d();
	//r.read_recepie();
	//  SensorDebug ss;
	//  ss.PrintInfraredValues();
	// ss.PrintColorValue();
//	UserInterface::buttonTest();

	return 0;
}	
