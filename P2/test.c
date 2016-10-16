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

matrix* frameTranslationRotationZAxis(float theta, matrix* origin, matrix* destG);
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
    matrix* c = (matrix*)calloc(1, sizeof(c));
    int i, j, k;
		c->rows = matA->rows;
		c->columns = matB->columns;

    c->data = malloc(sizeof(float* ) * matA->rows);

    for (i = 0; i < matA->rows; i++)
    {
        c->data[i] = malloc(sizeof(float) * matB->columns);

        for (k = 0; k < matB->columns; k++)
        {
            c->data[i][k] = 0.0;

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

void reset_arm(){
	enable_servos();
	set_servo_position(0, 230); //lower number moves up from shoulder
	set_servo_position(3, 1700); //higher number moves up from elbow
	sleep(1.0);
	disable_servos();
}

matrix* getAMatrix(int rows, int columns)
{
	matrix* mat = (matrix*)calloc(1, sizeof(mat));
	mat->rows = rows;
	mat->columns = columns;
	return mat;
}
int main()
{
	float theta = PI / 2.0;
	int i, j,r = 4, c = 1;
	matrix * robotG = (matrix*)calloc(1, sizeof(robotG));
	robotG->rows = 4;
	robotG->columns = 1;
	matrix * origin = (matrix*)calloc(1, sizeof(origin));
	origin->rows = 4;
	origin->columns = 1;
	matrix * destG = (matrix*)calloc(1, sizeof(destG));
	destG->rows = 4;
	destG->columns = 1;
	// declare rows
	robotG->data = (float**)malloc(robotG->rows * sizeof(float*));
	origin->data = (float**)malloc(origin->rows * sizeof(float*));
	destG->data = (float**)malloc(destG->rows * sizeof(float*));

	// declare columns
	for(i = 0; i < r; i++)
	{
		robotG->data[i] = (float*)malloc(robotG->columns * sizeof(float));
		origin->data[i] = (float*)malloc(origin->columns *  sizeof(float));
		destG->data[i] = (float*)malloc(destG->columns * sizeof(float));
	}

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
	matrix* tOD = (matrix*)calloc(1, sizeof(tOD));
	tOD->rows = 4;
	tOD->columns = 4;
	matrix* rOOP = (matrix*)calloc(1, sizeof(rOOP));
	rOOP->rows = 4;
	rOOP->columns = 4;
	tOD->data = calloc(4, sizeof(float)); // Translation matrix from Origin to destGination
	rOOP->data = calloc(4, sizeof(float)); // Rotation matrix from Origin to Origin Prime
	for(i = 0; i < 4;i++)
		{
			tOD->data[i] = calloc(4, sizeof(tOD[i]));
			rOOP->data[i] = calloc(4, sizeof(rOOP[i]));
		}

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
