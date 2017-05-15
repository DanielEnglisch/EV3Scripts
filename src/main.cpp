
#include "LineFollow.h"
#include "Claw.h"
int main(){
	robot r;
	Claw xx;
	//r.follow_line_d();
	xx.close(); // close claw
	xx.lift();
	xx.wait();
	xx.wait();
	xx.lower();
	xx.wait();
	xx.open(); // open claw
	//r.read_recepie(); // output cout

	return 0;
}	