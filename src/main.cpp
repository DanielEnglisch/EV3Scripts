#include <iostream>
#include "LineFollow.h"
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;	

int main(){
   	
   	// cout << "0;0;0" << endl;
    //    for(int r = 0; r<255; ++r){
    //    for(int g = 0; g<255; ++g){
    //    for(int b = 0; b<255; ++b){
    //        cout << r << ';'<< g << ';'<< b << endl;
    //        }
    //        }
    //        }
       
    robot r;

    motor r (OUTPUT_A);
    motor l (OUTPUT_D);  
    light_sensor s(INPUT_2);
    r.follow_line_until_stone(200);
    r.read_recepie();
    
    //r.get_stones;

   	cout << "0;0;0" << endl;

    return 0;
}

