
#include "ev3dev.h"
#include <iostream>
using namespace std;
using namespace ev3dev;
int main(){
cout << "beeping:" << endl;


sound::beep();
cout << "beeped!" << endl;
    return 0;
}

