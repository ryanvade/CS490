// Created on Mon Aug 22 2016
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
#define DISTANCEINTHREE 16.51 // cm
#define  DISTANCEINTHREEOFASQUARE 0.53
#define CIRCUMFERENCE PI * 6.5
#define MAXVELOCITY  5.5 // in cm/s

typedef struct {
	int x;
	int y;
} p;

typedef struct{
	int rows;
	int columns;
	float** data;
} matrix;

typedef int color;

matrix* getAMatrix(int rows, int columns)
 {
 	int i;
 	matrix* mat = (matrix*)calloc(1, sizeof(mat));
 	mat->rows = rows;
 	mat->columns = columns;
 	mat->data = (float**)calloc(rows, sizeof(float*));
 	for(i = 0; i < rows; i++)
 	{
 		mat->data[i] = (float*)calloc(columns, sizeof(float));
 	}
 	return mat;
}

 matrix* matrix_mult(matrix* matA, matrix* matB)
 {
 		int i, j, k;
     matrix* c = getAMatrix(matA->rows, matB->columns);
     for (i = 0; i < matA->rows; i++)
     {
         for (k = 0; k < matB->columns; k++)
         {
             for (j = 0; j < matA->columns; j++)
             {
                 c->data[i][k] += (matA->data[i][j]) * (matB->data[j][k]);
             }
         }
     }

     return c;
 }

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

void turn(int direction, float ticks)
{
	long tcks = (long)ticks * 10;
	if(direction)
	{
		// counter clock-wise
		mrp(LEFT_MOTOR, 500, -tcks);
		mrp(RIGHT_MOTOR, 500, tcks);
		bmd(RIGHT_MOTOR);
		mav(LEFT_MOTOR, 0);
		mav(RIGHT_MOTOR, 0);
		beep();
		sleep(0.5);
		
	}
	else
	{
		// clock-wise
		mrp(LEFT_MOTOR, 500, tcks);
		mrp(RIGHT_MOTOR, 500, -tcks);
		bmd(RIGHT_MOTOR);
		mav(LEFT_MOTOR, 0);
		mav(RIGHT_MOTOR, 0);
		beep();
		sleep(0.5);
	}
	
}

void turnToAngle(float angle)
{
	float distance = CIRCUMFERENCE * (angle / (2 * PI));
	printf("Distance: %f", distance);
	float ticks = ((2 * PI)/ CIRCUMFERENCE) * distance;
	printf("Ticks: %f", ticks);
	turn(1, ticks);
}

matrix* frameTranslationRotationZAxis(float theta, matrix* origin, matrix* destG)
{
	int i, j;
	matrix* tOD = getAMatrix(4, 4);
	matrix* rOOP = getAMatrix(4, 4);

	tOD->data[0][0] = 1.0; // (1,1)
	tOD->data[0][3] = destG->data[0][0]; // (1, 4)

	tOD->data[1][1] = 1.0; // (2, 1)
	tOD->data[1][3] = destG->data[1][0]; // (2, 4)

	tOD->data[2][2] = 1.0; // (3, 3)
	tOD->data[2][3] = origin->data[2][0]; // (3, 4)

	tOD->data[3][3] = destG->data[3][0];

	rOOP->data[0][0] = cos(theta); // (1,1)
	rOOP->data[0][1] = sin(theta); // (1,2)
	rOOP->data[0][3] = origin->data[0][0]; // (1,1)

	rOOP->data[1][0] = -1.0 * sin(theta); // (2,1)
	rOOP->data[1][1] = cos(theta); // (2,2)
	rOOP->data[1][3] = origin->data[1][0]; // (2,1)

	rOOP->data[2][2] = 1.0; // (3,3)
	rOOP->data[2][3] = origin->data[2][0]; // (3,1)

	rOOP->data[3][3] = origin->data[3][0]; // (4, 4)

	return matrix_mult(tOD, rOOP);
 }

 void printArray(matrix* mat)
 {

 	int i, j;
 	for(i = 0; i < mat->rows; i++)
 	{
 		for(j = 0; j < mat->columns; j++)
 		{
 			cbc_printf(0,0,"%f ", mat->data[i][j] );
 		}
 		printf("\n");
 	}
 }

 int myround(float f)
 {
 	return (f >= 0) ? (int)(f + 0.5) : (int)(f - 0.5);
 }



 float distancebetween(matrix* A, matrix* B) // from A to B (2D)
 {
 	float diffX = (B->data[0][B->columns - 1] - A->data[0][A->columns - 1]);
 	float diffY = (B->data[1][B->columns - 1] - A->data[1][A->columns - 1]);
 	return sqrt((diffX * diffX) + (diffY * diffY));
 }

 float distanceto(matrix* B) // from origin to B (2D)
 {
 	return sqrt((B->data[0][B->columns - 1] * B->data[0][B->columns - 1])
 						+ (B->data[1][B->columns - 1] * B->data[1][B->columns - 1]));
 }

 float angleto(matrix* B) // from origin to B (2D)
 {
 	return atan2(B->data[1][B->columns - 1], B->data[0][B->columns]) * (180 / PI);
 }

 float angleBetween(matrix* A, matrix* B) // from A to B (2D)
 {
 	float diffX = (B->data[0][B->columns - 1] - A->data[0][A->columns - 1]);
 	float diffY = (B->data[1][B->columns - 1] - A->data[1][A->columns - 1]);
 	return atan2(diffY, diffX) * (180 / PI);
 }

void reset_arm(){
	enable_servos();
	set_servo_position(SHOULDER, 230); //lower number moves up from shoulder
	set_servo_position(ELBOW, 1700); //higher number moves up from elbow
	sleep(1.0);
	disable_servos();
}


//converts radians to servo position. Still not accurate
void point_arm(float s_angle, float e_angle){
	enable_servos();
	if(s_angle > 0){  //positive angle
		s_angle = abs(s_angle);
		set_servo_position(SHOULDER, (int)(76 + ARM + (ARM * (cos(s_angle))))); 
		set_servo_position(ELBOW, (int)(ARM * cos(e_angle)));
	} else { //negative angle
		s_angle = abs(s_angle);
		set_servo_position(SHOULDER, (int)(ARM + ARM * (1.0 - cos(s_angle))) -76); 
		set_servo_position(ELBOW, (int)(ARM - (ARM * (1.0 - cos(e_angle)))));
	}

	//slowly point
	//necessary to drive forward?
	sleep(3.0);
	disable_servos();
	//reset_arm();
}

p select_coordinates(){
	//change y with up, down arrows
	//change x with right, left arrows
	//default location is (3, 0)
	//range is 0-6 in x, 0-5 in y
	p destination = {3, 0};
	//press B to set values
	do{
		sleep(SLEEP_INTERVAL);
		if(up_button()){
			destination.y = ((destination.y + 1) % 6);
		}
		if(down_button()){
			destination.y = abs((destination.y - 1) % 6);
		}
		if(right_button()){
			destination.x =((destination.x + 1) % 7);
		}
		if(left_button()){
			destination.x = abs((destination.x - 1) % 7);
		}
		cbc_display_clear();
		cbc_printf(0,0, "Destination: ( %d, %d )", destination.x, destination.y);
	} while(!b_button());
	cbc_display_clear();
	return destination;
}

color select_color(){
	//cycle through B, G, Y (no red?) by pressing A, select and return with B

	color current_color = 0;
	char* colors[3] = {"Red", "Yellow", "Blue"};
	do{
		sleep(SLEEP_INTERVAL);
		cbc_display_clear();
		cbc_printf(0,0,"Select a color\n");
		
		cbc_printf(0,3, colors[current_color]);
		if(a_button()){
			current_color = (current_color + 1) % 3;
		}
	} while(!b_button());
	cbc_display_clear();
	return current_color;
}

void moveAndBeep()
{
	motor(LEFT_MOTOR, 100);
	motor(RIGHT_MOTOR, 100);
	sleep(3);
	beep();
	// goes 16.5 cm
}

void turnAndBeep(int direction)
{
	if(direction) // counter clock wise
	{
		motor(LEFT_MOTOR, -255);
		motor(RIGHT_MOTOR, 255);
		sleep(3);
		motor(LEFT_MOTOR, 0);
		motor(RIGHT_MOTOR, 0);
	}
	else // clock wise
	{
		motor(LEFT_MOTOR, 255);
		motor(RIGHT_MOTOR, -255);
		sleep(3);
		motor(LEFT_MOTOR, 0);
		motor(RIGHT_MOTOR, 0);
	}
	
}


void go_to(matrix* origin, matrix* robotG, matrix* destG){
	int i;
	reset_arm();
	// face the point
	matrix* fGR = frameTranslationRotationZAxis(robotG->data[2][robotG->columns -1], origin, destG);
	printf("fGR: \n");
	printArray(fGR);
	matrix* destR = twoDimensionalMatrixMult(destG, fGR);
	printf("DestR: \n");
	printArray(destR);
	
	float angleToPoint = angleTo(destR);
	float distanceToPoint = distanceTo(destR);
	int movingIterations = myround(distanceToPoint / (float)DISTANCEINTHREE);
	
	turnToAngle(angleToPoint);
	robotG->data[2][robotG->columns - 1] += angleToPoint;
	
	for(i = 0; i < movingIterations; i++)
	{
		mav(LEFT_MOTOR, 500);
		mav(RIGHT_MOTOR, 500);
		sleep(3);
		beep();
		robotG->data[0][robotG->columns -1] += (DISTANCEINTHREEOFASQUARE * cos(robotG->data[2][robotG->columns - 1]));
		robotG->data[1][robotG->columns -1] += (DISTANCEINTHREEOFASQUARE * sin(robotG->data[2][robotG->columns - 1]));
		printf("Robot location in the global: ");
		printArray(robotG);
	}
}

void Point(int channel){
	p _p; //initialize a point in (x,y)
	int x, y;
	
	set_each_analog_state(1,0,0,1,1,0,1,1);
	sleep(0.2);
	track_update();
	//track_count(ch);

	//do something if blob is detected
	if(track_count(channel) > 0){
		_p.x = track_x(channel, 0);
		_p.y = track_y(channel, 0);
		
	}
	//check IR as well
	
}

/*void go_and_p(int x, int y, int color){
	reset_arm();
	go_to(x, y);
	Point(color);
}*/



int main() 
{
	cbc_printf(0,0, "Press A to start");
	char* behaviors[3] = {"Go To", "Point", "Go & Point"};
	short a_state = 0;
	color c = 0;
	p _p;
	while(1){
		sleep(SLEEP_INTERVAL);
		//listen for input
		//cycle through options with A button
		if(a_button()){
			a_state = (a_state + 1) % 3;
			cbc_display_clear();
			cbc_printf(0,0,behaviors[a_state]);
		}
		if(b_button()){
			switch(a_state){
				case 0:
					//f = &go_to;
					
					_p = select_coordinates();
					turn(CCW, 2.64);
					//go_to(_p.x, _p.y);
					//confirmation();
					break;
				case 1:
					reset_arm();
					//confirmation();
					break;
				case 2:
					_p = select_coordinates();
					c = select_color();
					Point(c);
					//confirmation();
					break;
			}
		}
	}
	return 0;
}
