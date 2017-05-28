#include <iostream>
#include "LineFollow.h"
#include "ev3dev.h"


using namespace ev3dev;	

int main(){
   	
   	std::cout << "0;0;0" << std::endl;
    //    for(int r = 0; r<255; ++r){
    //    for(int g = 0; g<255; ++g){
    //    for(int b = 0; b<255; ++b){
    //        cout << r << ';'<< g << ';'<< b << endl;
    //        }
    //        }
    //        }
       
    robot r;

//     motor mr (OUTPUT_A);
//     motor l (OUTPUT_D);  
// infrared_sensor ir(INPUT_1);
// 	ir.set_mode(infrared_sensor::mode_ir_prox);
// 	light_sensor line_sensor (INPUT_2);
// 	line_sensor.set_mode(light_sensor::mode_reflect);

//     r.follow_line_until_stone(200,mr,l,line_sensor,ir);
    r.read_recepie();
    
    //r.get_stones;

   	// cout << "0;0;0" << endl;
       int counter(0);
 while(!r.rec_fin) counter++;
    return 0;
}

