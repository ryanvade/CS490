// Created on Sun Oct 16 2016

#ifndef __GUI_H__ // Change FILE to your file's name
#define __GUI_H__

#include <stdio.h>

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2 
#define SLEEP_INTERVAL 0.15
#define SHOULDER 0
#define ELBOW 3
#define CLOCKWISE 1
#define CCW -1
#define FRONT_SENSOR 0
#define FRONT_LEFT_SENSOR 4
#define FRONT_RIGHT_SENSOR 6
#define PI 3.141592
#define ARM 1024.0
#define turn90time 2.64

void confirmation(){
	cbc_display_clear();
	cbc_printf(0,0, "Press Black button");
	cbc_printf(0, 3, "to start.");
	while(!black_button){
		sleep(0.25);
	}
	cbc_display_clear();
	cbc_printf(0,0, "Starting.");
	//beep();
	sleep(5.0);		
}



#endif
