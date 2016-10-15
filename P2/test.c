// Created on Sat Oct 1 2016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592;

float** twoDimensionalMatrixMult(float** A, int rowsA, int columnsA, float** B, int rowsB, int columnsB);
float** frameTranslationRotationZAxis(float theta, float** origin, float** dest);

void printArray(float** arr, int rowsArr, int columnsArr)
{

	int i, j;
	for(i = 0; i < rowsArr; i++)
	{
		for(j = 0; j < columnsArr; j++)
		{
			printf("%f ", arr[i][j] );
		}
		printf("\n");
	}
}

int main()
{
	float theta = 3.141592 / 2.0;
	int i, j,r = 4, c = 1;
	// declare rows
	float** robotG = (float**)malloc(r * sizeof(float*));
	float** origin = (float**)malloc(r * sizeof(float*));
	float** dest = (float**)malloc(r * sizeof(float*));

	// declare columns
	for(i = 0; i < r; i++)
	{
		robotG[i] = (float*)malloc(c * sizeof(float));
		origin[i] = (float*)malloc(c *  sizeof(float));
		dest[i] = (float*)malloc(c * sizeof(float));
	}

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 1; j++)
		{
			//robotG[i][j] = 0.0;
			origin[i][j] = 0.0;
			dest[i][j] = 0.0;
		}
	}

	robotG[0][0] = 3;
	robotG[1][0] = 3;
	robotG[2][0] = 0;
	robotG[3][0] = 1;

	origin[0][0] = 0.0;
	origin[1][0] = 0.0;
	origin[2][0] = 0.0;
	origin[3][0] = 1.0;

	dest[0][0] = 0.0;
	dest[1][0] = -2.0;
	dest[2][0] = 0.0;
	dest[3][0] = 1.0;
	printArray(robotG, r, c);
	printf("\n");
	printArray(origin, r, c);
	printf("\n");
	printArray(dest, r,c);

	// float** fGR = frameTranslationRotationZAxis(theta, origin, robotG);
	//
	// printf("robot G: \n");
	// printArray(robotG, r, c);
	// printf("\nfGR: \n");
	// printArray(fGR, 4, 4);
	// printf("\n");
	//
	// float** pointR = twoDimensionalMatrixMult(fGR, 4, 4, dest, 4, 1);
	// if(pointR == NULL)
	// {
	// 	printf("The Array is NULL\n");
	// }else
	// {
	// printArray(pointR, 1, 4);
	// }
	for(i = 0; i < r; i++)
	{
			free(robotG[i]);
			free(origin[i]);
			free(dest[i]);
			// free(pointR[i]);
	}
	// free(pointR);

	return 0;
}

float** twoDimensionalMatrixMult(float** A, int rowsA, int columnsA, float** B, int rowsB, int columnsB)
{
	int rA, cA, cB;
	int sum = 0.0;
	printf("Matrix Mult A: \n");
	printArray(A, rowsA, columnsA);
	printf("\nMatrix Mult B: \n");
	printArray(B, rowsB, columnsB);
	if(columnsA != rowsB)
	{
		return NULL;
	}

	float **result = calloc(rowsA, sizeof(float));
	for (rA = 0; rA < rowsA; rA++) {
		result[rA] = calloc(columnsB, sizeof(float));
	}

	for(rA = 0; rA < rowsA; rA++)
	{
		for(cA = 0; cA < columnsA; cA++)
		{
			for(cB = 0; cB < columnsB; cB++)
			{
				sum += A[rA][cB] * B[cB][cA];
			}
			result[rA][cA] = sum;
			sum = 0;
		}
	}
	printf("\n");
	return result;
}

float** frameTranslationRotationZAxis(float theta, float** origin, float** dest)
{
	int i, j;
	float** tOD = calloc(4, sizeof(float)); // Translation matrix from Origin to Destination
	float** rOOP = calloc(4, sizeof(float)); // Rotation matrix from Origin to Origin Prime
	for(i = 0; i < 4;i++)
		{
			tOD[i] = calloc(4, sizeof(tOD[i]));
			rOOP[i] = calloc(4, sizeof(rOOP[i]));
		}

	tOD[0][0] = 1.0; // (1,1)
	tOD[0][3] = (dest[0][0] == 0)? 0.0: -1.0 * dest[0][0]; // (1, 4)

	tOD[1][1] = 1.0; // (2, 1)
	tOD[1][3] = (dest[0][1] == 0)? 0.0: -1.0 * dest[1][0]; // (2, 4)

	tOD[2][2] = 1.0; // (3, 3)
	tOD[2][3] = (dest[0][2] == 0)? 0.0: -1.0 * dest[2][0]; // (3, 4)

	tOD[3][3] = dest[3][0];

	rOOP[0][0] = cos(theta); // (1,1)
	rOOP[0][1] = sin(theta); // (1,2)
	rOOP[0][3] = origin[0][0]; // (1,1)

	rOOP[1][0] = -1.0 * sin(theta); // (2,1)
	rOOP[1][1] = cos(theta); // (2,2)
	rOOP[1][3] = origin[0][1]; // (2,1)

	rOOP[2][2] = 1.0; // (3,3)
	rOOP[2][3] = origin[0][2]; // (3,1)

	rOOP[3][3] = origin[0][3]; // (4, 4)

	return twoDimensionalMatrixMult(tOD, 4, 4, rOOP, 4, 4);
 }
