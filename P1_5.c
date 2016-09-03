// Created on Tue Aug 30 2016

#include <stdio.h>

#define TIME_FOR_12_INCHES 5 // in seconds
#define TIME_FOR_90_DEGREES 5 // in second
#define TIME_FOR_CIRCLE 5 // in seconds

#define TICKS_FOR_12_INCHES 5
#define TICKS_FOR_90_DEGREES 5
#define TICKS_FOR_CIRCLE 5

#define DRIVE_MOTOR 0
#define TURN_MOTOR 1
int position = 0;

void driveTime(int velocity);
void drivePosition(int velocity);
void turnNinetyTime(int velocity);
void turnNinetyPosition(int velocity);
void circleTime(int velocity);
void circlePosition(int velocity);

int main() 
{
	// Drive 12 inches
	// pause 3 secods
	// Turn 90 Degrees
	while(!down_button())
	{
		printf("waiting for input");
		if(black_button())
		{
			position = 1;
			printf("Switching to position based");
		}
		if(left_button())
		{
			// left button is S-Turn
			if(position)
			{
				drivePosition(255);
				turnNinetyPosition(255);
				drivePosition(255);
				turnNinetyPosition(255);
				drivePosition(255);
				turnNinetyPosition(128);
				drivePosition(255);
				turnNinetyPosition(128);
			}
			else
			{
				driveTime(255);
			}
			position = 0;
		}
		else if(right_button())
		{
			// right button is circle
			if(position)
			{
				circlePosition(255);
			}
			else
			{
				circleTime(255);
			}
			position = 0;
		}
		else if(up_button())
		{
			// up button is up-and-back
			if(position)
			{
				drivePosition(255);
				sleep(3);
				drivePosition(255);
			}
			else
			{
				driveTime(255);
				sleep(3);
				driveTime(255);
			}
			position = 0;
		}
		sleep(0.001); // prevent the CBC from entering too tight of a loop
	}
	// done with the program
	ao(); // turn off all motors
	//alloff(); // I don't trust ao(); // apparently alloff() does not exist
	printf("All done boss");
	return 0;
}

void driveTime(int velocity)
{
	mav(DRIVE_MOTOR, velocity);
	sleep(TIME_FOR_12_INCHES);
	motor(DRIVE_MOTOR, 0);
}

void drivePosition(int velocity)
{
	mrp(DRIVE_MOTOR, velocity, TICKS_FOR_12_INCHES);
}

void turnNinetyTime(int velocity)
{
	mav(TURN_MOTOR, velocity);
	sleep(TIME_FOR_90_DEGREES);
	motor(TURN_MOTOR, 0);
}

void turnNinetyPosition(int velocity)
{
	mrp(TURN_MOTOR, velocity, TICKS_FOR_90_DEGREES);
}

void circleTime(int velocity)
{
	mav(TURN_MOTOR, velocity);
	sleep(TIME_FOR_CIRCLE);
	motor(TURN_MOTOR, 0);
}

void circlePosition(int velocity)
{
	mrp(TURN_MOTOR, velocity, TICKS_FOR_CIRCLE);
	mrp(DRIVE_MOTOR, velocity, TICKS_FOR_CIRCLE);
}
