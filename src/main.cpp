
#include <iostream>
#include "ev3dev.h"
#include "LineFollow.h"
using namespace ev3dev;
using namespace std;


int main(){
   	

    //    for(int r = 0; r<255; ++r){
    //    for(int g = 0; g<255; ++g){
    //    for(int b = 0; b<255; ++b){
    //        cout << r << ';'<< g << ';'<< b << endl;
    //        }
    //        }
    //        }
       
    robot r;
<<<<<<< HEAD
     motor mr (OUTPUT_A);
    motor l (OUTPUT_D);  
=======
<<<<<<< HEAD
    r.read_recepie();
        //r.get_stones();
=======
    //  motor mr (OUTPUT_A);
    // motor l (OUTPUT_D);  
>>>>>>> a4098f4f3eb07f48c91e40380515acfff02a6c52

    //  infrared_sensor ir(INPUT_1);
	//  ir.set_mode(infrared_sensor::mode_ir_prox);

	//     light_sensor line_sensor (INPUT_2);
	//     line_sensor.set_mode(light_sensor::mode_reflect);

   //  r.follow_line_until_stone(200,mr,l,line_sensor,ir);
<<<<<<< HEAD
  //  r.read_recepie();
   
    //r.turn(90, mr, l);
    // r.get_stones();
    r.test();
=======
   // r.read_recepie();
       r.get_stones();
>>>>>>> 7153dfd122577184d1e925115f3b5d60b3811634
    //r.test();
>>>>>>> a4098f4f3eb07f48c91e40380515acfff02a6c52
   	// // cout << "0;0;0" << endl;
    //   int counter(0);
    //  while(!r.rec_fin) counter++;
    //  r.test();
    return 0;
}
