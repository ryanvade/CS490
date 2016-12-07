#ifndef CBC_H
#define CBC_H

// CBC Libarary functions are wrapped by these functions to allow
// for offline testing using a dummy implementations of these signatures

// CBC functions
void cbcSleep(double time);

// Sensor functions
double getBlobSize(int colorChannel);
double getDistance(int port);
void waitForButton();

// Effector functions
void drive(double leftSpeed, double rightSpeed);
void stop();
void cbcBeep();


#endif

