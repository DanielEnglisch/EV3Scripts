
#include <iostream>
#include "ev3dev.h"
using namespace ev3dev;
using namespace std;


int main(){
   	
	cout << "Clawing" << endl;
	cout << "Clawing-GG" << endl;

		int pos = 200;
		int speed = 300;

		motor m_left(OUTPUT_A);
		motor m_right(OUTPUT_D);

		int pos_l = m_left.position();
		int pos_r = m_right.position();
		
		m_left.set_position_sp(-pos);
		m_right.set_position_sp(-pos);
		m_left.set_speed_sp(-speed);
		m_right.set_speed_sp(-speed);
		m_left.run_to_rel_pos();
		m_right.run_to_rel_pos();
		int counter(0);
		while(m_left.position() >= pos_l-pos && m_right.position() >= pos_r-pos) counter++;
		
	cout << "End Clawing" << endl;

    return 0;
}
