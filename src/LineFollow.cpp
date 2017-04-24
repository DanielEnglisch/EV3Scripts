#include "LineFollow.h"

//Test
void LineFollow::follow_line_d(){
	
	motor a (OUTPUT_D);
	motor b (OUTPUT_A);
	light_sensor s (INPUT_2);
	s.set_mode(light_sensor::mode_reflect);
	bool escape = false;
	double val;
	float throttle;
	
	while(!escape)
	{
		val = s.value();
		
		drive(val,1,1, a, b);
		
		a.run_forever();
		b.run_forever();
		
		escape = button::back.pressed();
	}
	a.stop();
	b.stop();
}

void LineFollow::drive(float steering, float throttle,int mode, motor a, motor b){
    float motA, motAS, motATS, motB, motBS, motBTS;
	int minSpeed = -200;
	int maxSpeed = 200;

    // if(throttle>0){ //funciona
    //     motATS=constrain(throttle*(1+steering), -1, 1);
    //     motBTS=constrain(throttle*(1-steering), -1, 1);
    // }else{
    //     motATS=constrain(throttle*(1-steering), -1, 1);
    //     motBTS=constrain(throttle*(1+steering), -1, 1);
    // }

    // if(throttle<0){
    //     motATS=constrain(throttle*(1-steering), -1, 1);
    //     motBTS=constrain(throttle*(1+steering), -1, 1);
    // }else{
    //     motATS=constrain(throttle*(1+steering), -1, 1);
    //     motBTS=constrain(throttle*(1-steering), -1, 1);
    // }

	// black 338
	// white 536
	
	steering = floatMap(steering,338,536,-1,1);

    if(mode==1 && throttle<0){
        motATS=constrain(throttle*(1-steering), -1, 1);
        motBTS=constrain(throttle*(1+steering), -1, 1);
    }else{
        motATS=constrain(throttle*(1+steering), -1, 1);
        motBTS=constrain(throttle*(1-steering), -1, 1);
    }

    if(mode==1){
        motAS=+steering*(1-abs(throttle));
        motBS=-steering*(1-abs(throttle));
    }else if(mode==0){
        motAS=0;
        motBS=0;
    }

    motA=constrain(motATS+motAS, -1, 1);
    motB=constrain(motBTS+motBS, -1, 1);
	
	cout << "motA: " << motA << endl;
	cout << "motB: " << motB << endl;

    if(motA>0){
        a.set_speed_sp(floatMap(motA,0,1,minSpeed,maxSpeed));
    }else if(motA<0){
        
        a.set_speed_sp(floatMap(abs(motA),0,1,minSpeed,maxSpeed));
    }else{
        a.set_speed_sp(0);
    }

    if(motB>0){
        b.set_speed_sp(floatMap(motB,0,1,minSpeed,maxSpeed));
    }else if(motB<0){
        b.set_speed_sp(floatMap(abs(motB),0,1,minSpeed,maxSpeed));
    }else{
        b.set_speed_sp(0);
    }
}

float LineFollow::floatMap(float vx, float v1, float v2, float n1, float n2){
	//this function maps vx in the range v1 to v2 to the new range n1 and n2
	
    // v1 start of range, v2 end of range, vx the starting number between the range
    float percentage = (vx-v1)/(v2-v1);
    // n1 start of new range, n2 end of new range
    return (n2-n1)*percentage+n1;
}

void  LineFollow::calibrate(){
	float white = 40;
	float black = 30;
}

void LineFollow::forward_motors(float correction){
	motor a(OUTPUT_A);
	motor d(OUTPUT_D);
	correction *= 10;
	
	if(correction > 0) {
		d.set_speed_sp(100);
		a.set_speed_sp(100 - correction*10);
	}
	else if(correction < 0){
		d.set_speed_sp(100-correction*10);
		a.set_speed_sp(100);			
	}
		a.run_forever();
		d.run_forever();
		
}