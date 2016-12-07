void cbcSleep(double time) {
    msleep((int)(time * 1000));
}


int getDistance(int port){
    int distance = analog10(port);
    return distance;
}


int getBlobSize(int colorChannel) {
    track_update();
    int area = track_size(colorChannel, 0);
    return area;
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

