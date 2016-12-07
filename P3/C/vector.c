#include "vector.h"


double *vectorAdd(double *A, double *B, int n) {
  double *out = calloc(N, sizeof(double *));
  for (int i = 0; i < N; i++) {
    out[i] = A[i] + B[i];
  }
  return out;
}

double *vectorSub(double *A, double *B, int n) {
  double *out = calloc(N, sizeof(double *));
  for (int i = 0; i < N; i++) {
    out[i] = A[i] - B[i];
  }
  return out;
}

double *hadamardMul(double *A, double *B, int n) {
  double *out = calloc(N, sizeof(double *));
  for (int i = 0; i < N; i++) {
    out[i] = A[i] * B[i];
  }
  return out;
}
    
double dotProduct(double *A, double *B, int n) {
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
