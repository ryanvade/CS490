#ifndef VECTOR_H
#define VECTOR_H

// Convience typedefs
typedef vec_t double *;
typedef mat_t double **;

// Element-wise vector math
double *vectorAdd(double *A, double *B, int n);
double *vectorSub(double *A, double *B, int n);
double *hadamardMul(double *A, double *B, int n);

// Dotproduct
double dotProduct(double *A, double *B, int n);

// Transposes
double **transpose(double *A, int N, int M);
double **transpose2D(double **A, int N, int M);
double ***transpose3D(double ***A, int N, int M, int O);

#endif

