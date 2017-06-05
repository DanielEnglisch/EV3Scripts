
#include "ev3dev.h"
#include <iostream>
#include "LineFollow.h"
#include "Claw.h"
using namespace ev3dev;
int main(){
// cout << "beeping:" << endl;
robot r;
r.follow_line_d();

// sound::beep();
// std::cout << "beeped!" << std::endl;
    return 0;
}

