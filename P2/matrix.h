// Created on Sun Oct 16 2016

#ifndef __MATRIX_H__ // Change FILE to your file's name
#define __MATRIX_H__

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

typedef struct{
	int rows;
	int columns;
	float** data;
} matrix;

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


#endif
