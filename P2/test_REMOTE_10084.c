// Created on Sat Oct 1 2016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

typedef struct{
	int rows;
	int columns;
	float** data;
} matrix;

void reset_arm();
int myround(float f);
float angleto(matrix* B);
float distanceto(matrix* B);
void printArray(matrix* mat);
float angleBetween(matrix* A, matrix* B);
matrix* getAMatrix(int rows, int columns);
float distancebetween(matrix* A, matrix* B);
matrix* matrix_mult(matrix* matA, matrix* matB);
matrix* frameTranslationRotationZAxis(float theta, matrix* origin, matrix* destG);

int main()
{
	float theta = PI / 2.0;
	int i, j,r = 4, c = 1;
	matrix * robotG = getAMatrix(4, 1);
	matrix * origin = getAMatrix(4, 1);
	matrix * destG = getAMatrix(4, 1);

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 1; j++)
		{
			robotG->data[i][j] = 0.0;
			origin->data[i][j] = 0.0;
			destG->data[i][j] = 0.0;
		}
	}

	robotG->data[0][0] = 0.0;
	robotG->data[1][0] = 2.0;
	robotG->data[2][0] = theta;
	robotG->data[3][0] = 1;

	origin->data[0][0] = 0.0;
	origin->data[1][0] = 0.0;
	origin->data[2][0] = 0.0;
	origin->data[3][0] = 1.0;

	destG->data[0][0] = 3.0;
	destG->data[1][0] = 3.0;
	destG->data[2][0] = 0.0;
	destG->data[3][0] = 1.0;

	matrix* fGR = frameTranslationRotationZAxis(theta, origin, robotG);
	matrix* pointRobot = matrix_mult(fGR, destG);
	for(i = 0; i < r; i++)
	{
			free(robotG->data[i]);
			free(origin->data[i]);
			free(destG->data[i]);
			free(pointRobot->data[i]);
	}
	free(robotG);
	free(origin);
	free(destG);
	free(pointRobot);

	return 0;
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

 void printArray(matrix* mat)
 {

 	int i, j;
 	for(i = 0; i < mat->rows; i++)
 	{
 		for(j = 0; j < mat->columns; j++)
 		{
 			printf("%f ", mat->data[i][j] );
 		}
 		printf("\n");
 	}
 }

 int myround(float f)
 {
 	return (f >= 0) ? (int)(f + 0.5) : (int)(f - 0.5);
 }

 matrix* matrix_mult(matrix* matA, matrix* matB)
 {
 		int i, j, k;
     matrix* c = getAMatrix(mata->rows, matB->columns);
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

 void reset_arm()
 {
 	enable_servos();
 	set_servo_position(0, 230); //lower number moves up from shoulder
 	set_servo_position(3, 1700); //higher number moves up from elbow
 	sleep(1.0);
 	disable_servos();
 }
