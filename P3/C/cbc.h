#ifndef CBC_H
#define CBC_H

// CBC Libarary functions are wrapped by these functions to allow
// for offline testing using a dummy implementations of these signatures

// CBC functions
void cbcSleep(double time);

// Sensor functions
int getBlobSize(int colorChannel);
int getDistance(int port);

// Effector functions
void drive(double leftSpeed, double rightSpeed);
void stop();
void cbcBeep();


#endif
