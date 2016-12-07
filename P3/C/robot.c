#include "cbc.h"
#include "network.h"

#include <stdio.h>

#define RIGHT_RANGE 0
#define LEFT_RANGE 4
#define CAMERA_INPUT 5

#define ACTION_DRIVE 0
#define ACTION_TURN_LEFT 1
#define ACTION_TURN_RIGHT 2
#define ACTION_STOP 3
#define ACTION_THRESHOLD 0.5

#define CYAN 0

#define DRIVE_SPEED 0.5
#define TURN_SPEED 0.5

// Collect a vector for all the inputs to the nerual network
void sense(double *inputVector) {
    for(int i = RIGHT_RANGE; i <= LEFT_RANGE; i++)
        inputVector[i] = getDistance(i);
    inputVector[CAMERA_INPUT] = getBlobSize(CYAN);
}


// Act on the output of the nerual network
int act(double *outputs) {
    // Find the output with the highest activation
    int action;
    for(int i = 0; i < 3; i ++)
        if(outputs[i] > outputs[action])
            action = i;

    // Verify the action is actually activated
    if(outputs[action] < ACTION_THRESHOLD)
        action = ACTION_STOP;

    // Perform the action
    switch(action) {
        case ACTION_DRIVE:
            drive(DRIVE_SPEED, DRIVE_SPEED);
            break;

        case ACTION_TURN_LEFT:
            drive(-TURN_SPEED, TURN_SPEED);
            break;

        case ACTION_TURN_RIGHT:
            drive(TURN_SPEED, -TURN_SPEED);
            break;

        case ACTION_STOP:
            stop();
            break;
    }
    return action;
}

int main(int argc, char **argv) {
    // Initialize a network with 5 inputs, 3 outputs, and 2 hidden layers with 
    // nodes each
    Network network;
    int sizes[] = {5, 4, 4, 3};
    initializeNetwork(&network, 2, sizes);

    // Buffers for storing network input and output
    double inputs[5];
    double outputs[3];

    int behavior = ACTION_DRIVE;

    // Wait for start
    printf("Waiting for start button\n");
    waitForButton();
    printf("Going...");

    cbcSleep(3.0);

    // As long as we haven't found a safe place
    while(behavior != ACTION_STOP) {
        // Capture the sensor data
        sense(inputs);

        // Feed the data into the neural net
        forwardPropagate(&network, inputs, outputs);

        // Act on the decision of the network
        behavior = act(outputs);
        printf("Executing action: %d\n", behavior);

        // Give the action time to happen
        cbcSleep(1.0);
    }

    // Beep and exit
    for(int n = 0; n < 3; n++) {
        cbcBeep();
        cbcSleep(0.5);
    }

    return 0;
}

