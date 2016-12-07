#include "cbc.h"

#include <stdio.h>

void cbcSleep(double time) {
    printf("Sleep %fs\n", time);
}


double getDistance(int port){
    return 0.0;
}


double getBlobSize(int colorChannel) {
    return 0.0;
}


void waitForButton() {
    printf("Wait for button\n");
}


void drive(double leftSpeed, double rightSpeed) {
    printf("Drive: %f %f\n", leftSpeed, rightSpeed);
}


void stop() {
    printf("Stop\n");
}


void cbcBeep() {
    printf("Beep\n");
}

