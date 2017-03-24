#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H

class LineFollow
{
public:
	void vorprojekttag();
	void debugLightValues();
	void follow_line_new_pid();
	void forward_motors(float correction);
	void calibrate();
	void  follow_line_p();

};

#endif // LINEFOLLOW_H
