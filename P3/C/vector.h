#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Convience typedefs
typedef double* vec_t;
typedef double** mat_t;

// Element-wise vector math
vec_t vectorAdd(vec_t A, vec_t B, size_t n);
vec_t vectorSub(vec_t A, vec_t B, size_t n);
vec_t vectorScale(vec_t A, double s, size_t n);
vec_t hadamardMul(vec_t A, vec_t B, size_t n);

// Dotproduct
double dotProduct(vec_t A, vec_t B, size_t n);

// Transposes
double **transpose(double *A, int N, int M);
double **transpose2D(double **A, int N, int M);
double ***transpose3D(double ***A, int N, int M, int O);

vec_t matrixTimesVector(mat_t, vec_t, size_t m, size_t n);

#endif

