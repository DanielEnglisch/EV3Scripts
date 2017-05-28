#include <iostream>
#include "LineFollow.h"
using namespace std;
int main(){
   	
   cout << "0;0;0" << endl;
   for(int r = 0; r<255; r+=25)
   	cout << r << ';'<< r << ';'<< r << endl;
   	cout << "0;0;0" << endl;


   	robot r();
   	r.test();

    return 0;
}

