
#include "ev3dev.h"
#include <iostream>
#include "LineFollow.h"
#include "Claw.h"
using namespace ev3dev;
int main(){
// cout << "beeping:" << endl;
// motor rm(OUTPUT_A);
// motor lm(OUTPUT_D);
robot r;
r.read_recepie();
r.wait();
r.wait();
r.wait();
// Claw t;
r.wait();
r.get_stones();
// t.open();
// t.lift();
// t.close();
// t.half_lower();
// t.open();
// t.lower();
// t.close();
// t.lift();
// t.open();
// t.half_lower();

// sound::beep();
// std::cout << "beeped!" << std::endl;
    return 0;
}

