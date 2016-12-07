#include "cbc.h"

void cbcSleep(double time) {
    msleep((int)(time * 1000));
}


double getDistance(int port){
    int distance = analog10(port);
    return pow(distance, -1.34);
}


double getBlobSize(int colorChannel) {
    track_update();
    int area = track_size(colorChannel, 0);
    return area / 18921.0;
}


void drive(double leftSpeed, double rightSpeed) {
    motor(LEFT_MOTOR, (int)(leftSpeed * 100));
    motor(RIGHT_MOTOR, (int)(rightSpeed * 100));
}


void stop() {
    ao();
}


void cbcBeep() {
    beep();
}

