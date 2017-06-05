
#include "ev3dev.h"
#include <iostream>
#include "LineFollow.h"
#include "Claw.h"
using namespace ev3dev;
int main(){
// cout << "beeping:" << endl;
motor rm(OUTPUT_A);
motor lm(OUTPUT_D);
robot r;
r.test();

// sound::beep();
// std::cout << "beeped!" << std::endl;
    return 0;
}

