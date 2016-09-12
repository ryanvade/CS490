// Created on Tue Aug 30 2016
// Last Updated on Sunday Sept 12 2016
// Ryan Owens & Zack Anderson
// CS 490
// Project 1
#include <stdio.h>

#define TIME_FOR_12_INCHES 8.5 // in seconds
#define TIME_FOR_90_DEGREES 6 // in second
#define TIME_FOR_CIRCLE 43 // in seconds

#define TICKS_FOR_12_INCHES 9685
#define TICKS_FOR_90_DEGREES 4400 // works fine for right turns, not left so we compensate
#define TICKS_FOR_CIRCLE_TURN 18000
#define TICKS_FOR_CIRCLE_DRIVE 46000

#define DRIVE_MOTOR 0
#define TURN_MOTOR 1
int position = 0;

void driveTime(int velocity);
void drivePosition(int ticks, int velocity);
void turnNinetyTime(int velocity);
void turnNinetyPosition(int ticks, int velocity);
void circleTime(int velocity);
void circlePosition(int velocity);
void leftBox();
void rightBox();

int main() 
{
	// Drive 12 inches
	// pause 3 secods
	// Turn 90 Degrees
	printf("waiting for input\n");
	while(!down_button())
	{
		if(black_button())
		{
			if(position)
			{
				printf("\nSwitching to time based\n");
				position = 0;
			}else
			{
				printf("\nSwitching to position based\n");
				position = 1;
			}
			sleep(1);
		}
		
		if(a_button())
		{
			leftBox();
		}
		else if(b_button())
		{
			rightBox();
		}
		else if(left_button())
		{
			// left button is S-Turn
			if(position)
			{
				printf("S-TURN mrp\n");
				beep();
				sleep(1);
				beep();
				sleep(1);
				beep();
				sleep(1);
				
				drivePosition(TICKS_FOR_12_INCHES, 1000);
				turnNinetyPosition(TICKS_FOR_90_DEGREES, 1000);
				
				drivePosition(TICKS_FOR_12_INCHES,1000);
				turnNinetyPosition(TICKS_FOR_90_DEGREES, 1000);
				
				drivePosition(TICKS_FOR_12_INCHES,1000);
				turnNinetyPosition(-TICKS_FOR_90_DEGREES, 1000);
				
				drivePosition(TICKS_FOR_12_INCHES,1000);
				turnNinetyPosition(-TICKS_FOR_90_DEGREES, 1000);
				
				drivePosition(TICKS_FOR_12_INCHES,1000);
				off(DRIVE_MOTOR);
				off(TURN_MOTOR);
			}
			else
			{
				printf("S-TURN\n");
				beep();
				sleep(1);
				beep();
				sleep(1);
				beep();
				sleep(1);
				
				driveTime(1000);
				turnNinetyTime(1000);
				
				driveTime(1000);
				turnNinetyTime(1000);
				
				driveTime(1000);
				turnNinetyTime(-1000);
				
				driveTime(1000);
				turnNinetyTime(-1000);
				
				driveTime(1000);
			}
			position = 0;
				beep();
				sleep(.5);
				beep();
			printf("waiting for input\n");
		}
		else if(right_button())
		{
			// right button is circle

			if(position)
			{
				printf("Circle mrp\n");
				beep();
				sleep(1);
				beep();
				sleep(1);
				beep();
				sleep(1);
				
				circlePosition(1000);
				off(DRIVE_MOTOR);
				off(TURN_MOTOR);
			}
			else
			{
				printf("Circle\n");
				beep();
				sleep(1);
				beep();
				sleep(1);
				beep();
				sleep(1);
				
				circleTime(1000);
			}
			position = 0;
				beep();
				sleep(.5);
				beep();
			printf("waiting for input\n");
		}
		else if(up_button())
		{
			// up button is up-and-back

			if(position)
			{
				printf("Up-and-Back mrp\n");
				beep();
				sleep(1);
				beep();
				sleep(1);
				beep();
				sleep(1);
				
				drivePosition(TICKS_FOR_12_INCHES, 1000);
				
				beep();
				sleep(3);
				
				drivePosition(-TICKS_FOR_12_INCHES, 1000);
			}
			else
			{
				printf("Up-and-Back\n");
				beep();
				sleep(1);
				beep();
				sleep(1);
				beep();
				sleep(1);
				
				driveTime(1000);
				
				beep();
				sleep(3);
				
				driveTime(-1000);
			}
			position = 0;
				beep();
				sleep(.5);
				beep();
			printf("waiting for input\n");
		}
		sleep(0.01); // prevent the CBC from entering too tight of a loop
	}
	// done with the program
	ao(); // turn off all motors
	printf("All done boss");
	return 0;
}

void driveTime(int velocity)
{
	mav(DRIVE_MOTOR, velocity);
	//mav(TURN_MOTOR, -velocity/18);
	freeze(TURN_MOTOR);
	sleep(TIME_FOR_12_INCHES);
	motor(DRIVE_MOTOR, 0);
	motor(TURN_MOTOR, 0);
}

void drivePosition(int ticks, int velocity)
{
	freeze(TURN_MOTOR);
	mrp(DRIVE_MOTOR, velocity, ticks);
	bmd(DRIVE_MOTOR);
	motor(DRIVE_MOTOR, 0);
}

void turnNinetyTime(int velocity)
{
	freeze(DRIVE_MOTOR);
	if(velocity < 0)
	{
		mav(TURN_MOTOR, velocity);
		sleep(TIME_FOR_90_DEGREES + 0.60);
	}else
	{
		mav(TURN_MOTOR, velocity);
		sleep(TIME_FOR_90_DEGREES);
	}
	motor(TURN_MOTOR, 0);
}

void turnNinetyPosition(int ticks, int velocity)
{
	if(ticks < 0) ticks -= 120; // for left turns attempt to compensate
	mrp(TURN_MOTOR, velocity, ticks);
	bmd(TURN_MOTOR);
	motor(TURN_MOTOR, 0);
}

void circleTime(int velocity)
{
	mav(TURN_MOTOR, velocity / 2.7  );
	mav(DRIVE_MOTOR, velocity);
	sleep(TIME_FOR_CIRCLE);
	motor(TURN_MOTOR, 0);
	motor(DRIVE_MOTOR, 0);
}

void circlePosition(int velocity)
{
	
	mrp(TURN_MOTOR, velocity / 2.7, TICKS_FOR_CIRCLE_TURN);
	mrp(DRIVE_MOTOR, velocity, TICKS_FOR_CIRCLE_DRIVE);
	bmd(TURN_MOTOR);
	
}

void leftBox()
{
				driveTime(1000);
				turnNinetyTime(-1000);
				
				driveTime(1000);
				turnNinetyTime(-1000);
				
				driveTime(1000);
				turnNinetyTime(-1000);
				
				driveTime(1000);
				turnNinetyTime(-1000);
}

void rightBox()
{
				driveTime(1000);
				turnNinetyTime(1000);
				
				driveTime(1000);
				turnNinetyTime(1000);
				
				driveTime(1000);
				turnNinetyTime(1000);
				
				driveTime(1000);
				turnNinetyTime(1000);
}
