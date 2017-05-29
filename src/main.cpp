
#include "LineFollow.h"
#include "support/SensorDebug.h"
#include "Claw.h"

void readRecipe(){
    robot r;
    r.read_recepie();
}

void getStone(){
    robot r;
    r.get_stones();
}

int main(){
   	
    getStone();
    //SensorDebug sd;
    //sd.PrintColorValue();
    //robot r;
    //r.test();
    //r.follow_line_d();
    //Claw c;
    //c.close();
    //c.wait();
    //c.open();


    return 0;
}

