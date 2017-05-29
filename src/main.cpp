
#include "LineFollow.h"
#include "support/SensorDebug.h"


void readRecipe(){
    robot r;
    r.read_recepie();
}

void getStone(){
    robot r;
    r.get_stones();
}

int main(){
   	
    //getStone();
    SensorDebug sd;
    sd.PrintColorValue();
    return 0;
}

