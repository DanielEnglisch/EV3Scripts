
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
    r.read_recepie();
        //r.get_stones();
    //r.test();
   	// // cout << "0;0;0" << endl;
    //   int counter(0);
    //  while(!r.rec_fin) counter++;
    //  r.test();
    return 0;
}
