// Created on Tue Oct 11 2016

#include <stdio.h>

int main() 
{
	set_each_analog_state(1, 0, 0, 1, 1, 0, 1, 1);
	while(!b_button())
	{
		printf("Port %d = %d", 3, analog10(3));
		printf(" Port %d = %d", 4, analog10(4));
		printf(" Port %d = %d", 0, analog10(0));
		printf(" Port %d = %d", 6, analog10(6));
		printf(" Port %d = %d\n", 7, analog10(7));
		sleep(1);
	}
}
