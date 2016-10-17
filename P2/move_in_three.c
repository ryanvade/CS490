// Created on Sun Oct 16 2016

#include <stdio.h>
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
#define PI 3.141592
#define CIRCUMFERENCE PI * 6.5
#define MAXVELOCITY  5.5 // in cm/s

// time in seconds
void turn(int direction, float ticks)
{
	long tcks = (long)ticks * 10;
	if(direction)
	{
		// counter clock-wise
		mrp(LEFT_MOTOR, 500, -tcks);
		mrp(RIGHT_MOTOR, 500, tcks);
		bmd(RIGHT_MOTOR);
		mav(LEFT_MOTOR, 0);
		mav(RIGHT_MOTOR, 0);
		beep();
		sleep(0.5);
		
	}
	else
	{
		// clock-wise
		mrp(LEFT_MOTOR, 500, tcks);
		mrp(RIGHT_MOTOR, 500, -tcks);
		bmd(RIGHT_MOTOR);
		mav(LEFT_MOTOR, 0);
		mav(RIGHT_MOTOR, 0);
		beep();
		sleep(0.5);
	}
	
}

void turnToAngle(float angle)
{
	float distance = CIRCUMFERENCE * (angle / (2 * PI));
	printf("Distance: %f", distance);
	float ticks = ((2 * PI)/ CIRCUMFERENCE) * distance;
	printf("Ticks: %f", ticks);
	turn(1, ticks);
}

int main() 
{
	float angle = PI;
	turnToAngle(angle);
	return 0;
}
