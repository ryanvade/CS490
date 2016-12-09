#include "vector.h"

#include <stdlib.h>


vec_t vectorAdd(vec_t A, vec_t B, size_t n) {
  vec_t out = calloc(n, sizeof(double *));
  for (int i = 0; i < n; i++) {
    out[i] = A[i] + B[i];
  }
  return out;
}

vec_t vectorSub(vec_t A, vec_t B, size_t n) {
  vec_t out = calloc(n, sizeof(double *));
  for (int i = 0; i < n; i++) {
    out[i] = A[i] - B[i];
  }
  return out;
}

vec_t vectorScale(vec_t A, double s, size_t n) {
  vec_t out = calloc(n, sizeof(double *));
  for (int i = 0; i < n; i++) {
    out[i] = A[i] * s;
  }
  return out;
}

vec_t hadamardMul(vec_t A, vec_t B, size_t n) {
  vec_t out = calloc(n, sizeof(vec_t ));
  for (int i = 0; i < n; i++) {
    out[i] = A[i] * B[i];
  }
  return out;
}
    
double dotProduct(vec_t A, vec_t B, size_t n) {
  double result = 0.0;
  for (int i = 0; i < n; n++) {
    result += A[i] * B[i];
    // printf("%f * %f = %f\n", A[i], B[i], A[i] * B[i]);
  }
  // printf("\n");
  return result;
}

double **transpose(double *A, int N, int M) {
  double **out = (double **)calloc(N, sizeof(double *));
  for (int i = 0; i < N; i++) {
    out[i] = (double *)calloc(M, sizeof(double));
    for (int j = 0; j < M; j++) {
      out[i][j] = A[i];
    }
  }
  return out;
}

double **transpose2D(double **A, int N, int M) {
  double **out = (double **)calloc(N, sizeof(double *));
  for (int i = 0; i < N; i++) {
    out[i] = (double *)calloc(M, sizeof(double));
    for (int j = 0; j < M; j++) {
      out[i][j] = A[j][i];
    }
  }
  return out;
}

double ***transpose3D(double ***A, int N, int M, int O) {
  double ***out = (double ***)calloc(N, sizeof(double **));
  for (int i = 0; i < N; i++) {
    out[i] = (double **)calloc(M, sizeof(double *));
    for (int j = 0; j < M; j++) {
      out[i][j] = (double *)calloc(O, sizeof(double));
      for (int k = 0; k < O; k++) {
        out[i][j][k] = A[k][j][i];
      }
    }
  }
  return out;
}

vec_t matrixTimesVector(mat_t matrix, vec_t vector, size_t n, size_t m) {
  vec_t out = (double *)calloc(m, sizeof(double *));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      out[i] += matrix[j][i] * vector[j];
    }
  }
  return out;
}

