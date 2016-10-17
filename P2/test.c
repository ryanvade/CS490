// Created on Sat Oct 1 2016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592; 

int** twoDimensionalMatrixMult(int** A, int rowsA, int columnsA, int** B, int rowsB, int columnsB);
int** frameTranslationRotationZAxis(float theta, int** origin, int** dest);

void printArray(float* arr, int rowsArr, int columnsArr)
{

	int i, j;
	for(i = 0; i < rowsArr; i++)
	{
		for(j = 0; j < columnsArr; j++)
		{
			printf("%f ", arr[i * sizeof(arr) + j] );
		}
		printf("\n");
	}
}

int main() 
{
	float theta = 3.141592 / 2.0;
	int i, j;
	
	int** pointG = calloc(1, sizeof(pointG));
	for(i = 0; i < 1; i++)
	{
		pointG[i] = calloc(4, sizeof(pointG));
	}
	
	pointG[0][0] = 3;
	pointG[0][1] = 3;
	pointG[0][2] = 0;
	pointG[0][3] = 1;
	
	int** origin = calloc(1, sizeof(origin));
	for(i = 0; i < 1;i++)
	{
		origin[i] = calloc(4, sizeof(origin));
	}
	origin[0][0] = 0;
	origin[0][1] = 0;
	origin[0][2] = 0;
	origin[0][3] = 1;
	
	int** dest = calloc(1, sizeof(dest));
	for(i = 0; i < 1; i++)
	{
		dest[i] = calloc(4, sizeof(dest));
	}
	dest[0][0] = 0.0;
	dest[0][1] = -2.0;
	dest[0][2] = 0.0;
	dest[0][3] = 1.0;
		
	int** fGR = frameTranslationRotationZAxis(theta, origin, dest);
	
	printArray(pointG, 1, 4);
	printf("\n");
	printArray(fGR, 4, 4);
	printf("\n");
	
	int** pointR = twoDimensionalMatrixMult(pointG, 1, 4, fGR, 4, 4);
	if(pointR == NULL)
	{
		printf("The Array is NULL\n");
	}else
	{
	printArray(pointR, 1, 4);
	}
	free(origin);
	free(dest);
	free(pointG);
	free(pointR);
	
	return 0;
}

float* twoDimensionalMatrixMult(float* A, int rowsA, int columnsA, float* B, int rowsB, int columnsB)
{
	int rA, cA, cB;
	int sum = 0.0;
	printf("A: \n");
	printArray(A, rowsA, columnsA);
	printf("\nB: \n");
	printArray(B, rowsB, columnsB);
	if(columnsA != rowsB)
	{
		return NULL;
	}
	
	float *result = malloc(rowsA * columnsB *  sizeof(result));
	for(rA = 0; rA < rowsA; rA++)
	{
		for(cB = 0; cB < columnsB; cB++)
		{
			result[rA * sizeof(result) + cB] = 0;
		}
	}
		
	for(rA = 0; rA < rowsA; rA++)
	{
		for(cA = 0; cA < columnsA; cA++)
		{
			for(cB = 0; cB < columnsB; cB++)
			{ 
				sum += A[rA * sizeof(A) + cB] * B[cB * sizeof(B) + cA];
			}
			result[rA * sizeof(result) + cA] = sum;
			sum = 0;
		}
	}
	printf("\n");
	return result;
}

float* frameTranslationRotationZAxis(float theta, float* origin, float* dest)
{
	int i, j;
	float* tOD = malloc(4 * 4 * sizeof(tOD)); // Translation matrix from Origin to Destination
	float* rOOP = malloc(4 * 4 * sizeof(rOOP)); // Rotation matrix from Origin to Origin Prime
	for(i = 0; i < 4;i++)
		for (j = 0; j < 4; j++)
		{
			tOD[i * sizeof(tOD) + j] = 0;
			rOOP[i * sizeof(rOOP) + j] = 0;
		}

	tOD[0 * sizeof(tOD) + 0] = 1.0; // (1,1)
	tOD[0 * sizeof(tOD) + 3] = (dest[0] == 0)? 0.0: -1.0 * dest[0]; // (1, 4)

	tOD[1 * sizeof(tOD) + 1] = 1.0; // (2, 1)
	tOD[1 * sizeof(tOD) + 3] = (dest[1] == 0)? 0.0: -1.0 * dest[1]; // (2, 4)
	
	tOD[2 * sizeof(tOD) + 2] = 1.0; // (3, 3)
	tOD[2 * sizeof(tOD) + 3] = (dest[2] == 0)? 0.0: -1.0 * dest[2]; // (3, 4)

	tOD[3 * sizeof(tOD) + 3] = dest[3];

	rOOP[0 * sizeof(rOOP) + 0] = cos(theta); // (1,1)
	rOOP[0 * sizeof(rOOP) + 1] = sin(theta); // (1,2)
	rOOP[0 * sizeof(rOOP) + 3] = origin[0]; // (1,1)

	rOOP[1 * sizeof(rOOP) + 0] = -1.0 * sin(theta); // (2,1)
	rOOP[1 * sizeof(rOOP) + 1] = cos(theta); // (2,2)
	rOOP[1 * sizeof(rOOP) + 3] = origin[1]; // (2,1)

	rOOP[2 * sizeof(rOOP) + 2] = 1.0; // (3,3)
	rOOP[2 * sizeof(rOOP) + 3] = origin[2]; // (3,1)

	rOOP[3 * sizeof(rOOP) + 3] = origin[3]; // (4, 4)
	
	return twoDimensionalMatrixMult(tOD, 4, 4, rOOP, 4, 4);
 }
