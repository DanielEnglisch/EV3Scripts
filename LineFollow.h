#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H

#include "ev3dev.h"

using ev3dev::motor;

class LineFollow
{
public:
	//DEBUG VALUES
	void debugColorValue();
	void debugInfraredValues();
	void debugGyroValues();
	void debugLightValues();
	
	void vorprojekttag();
	void follow_line_new_pid();
	void forward_motors(float correction);
	void calibrate();
	void follow_line_p();
	void follow_line_s();
	float floatMap(float vx, float v1, float v2, float n1, float n2);
	void drive(float steering, float throttle,int mode, motor a, motor b);

};

#endif // LINEFOLLOW_H
