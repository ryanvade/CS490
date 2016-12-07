#include "Network.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double sigmoidPrime(double x) { return pow(exp(-x) / ((1 + exp(-x))), 2); }
double costPrime(double x) { return 0.0; }
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

void initializeNetwork(Network *network, int numHiddenLayers, int *layerSizes) {
  network->layerCount = numHiddenLayers + 2;
  network->layerSizes = layerSizes;
  network->layers = (double **)calloc(numHiddenLayers + 2, sizeof(double *));
  network->biases = (double **)calloc(numHiddenLayers + 2, sizeof(double *));
  network->weights = (double ***)calloc(numHiddenLayers + 1, sizeof(double **));

  for (int i = 0; i < numHiddenLayers + 2; i++) {
    network->layers[i] = (double *)calloc(layerSizes[i], sizeof(double));
    network->biases[i] = (double *)calloc(layerSizes[i], sizeof(double));
    for (int j = 0; j < layerSizes[i]; j++) {
      network->layers[i][j] = 0.0;
      network->biases[i][j] = 0.5;
    }
  }

  for (int layer = 1; layer < numHiddenLayers + 2; layer++) {
    network->weights[layer] =
        (double **)calloc(layerSizes[layer], sizeof(double *));
    for (int node = 0; node < layerSizes[layer]; node++) {
      network->weights[layer][node] =
          (double *)calloc(layerSizes[layer - 1], sizeof(double));
      for (int w = 0; w < layerSizes[layer - 1]; w++) {
        network->weights[layer][node][w] = 0.5;
      }
    }
  }
}
void deleteNetwork(Network *network) {
  for (int l = 0; l < network->layerCount; l++) {
    free(network->layers[l]);
    free(network->biases[l]);
    free(network->weights[l]);
  }
  free(network->layers);
  free(network->biases);
  free(network->weights);
  free(network->layerSizes);
  network->layerCount = 0;
  free(network);
}

void forwardPropogate(Network *network, double *inputs) {
  // set the inputs
  printf("%d", network->layerSizes[0]);
  for (int i = 0; i < network->layerSizes[0]; i++) {
    network->layers[0][i] = inputs[i];
    printf("0 %f ", network->layers[0][i]);
  }
  // for every bias and weight in the network
  // add the sigmoid of dot product between weights, inputs + b
  for (int l = 1; l < network->layerCount; l++) {
    for (int n = 0; n < network->layerSizes[n]; n++) {
      network->layers[l][n] =
          sigmoid(dotProduct(network->weights[l][n], network->layers[l - 1],
                             network->layerSizes[l - 1]) +
                  network->biases[l][n]);
    }
  }
}

void backPropogate(Network *net, double *inputs, double *expectedOutputs) {
  forwardPropogate(net, inputs);
  // actual outputs from the network
  double *outputs = net->layers[net->layerCount - 1];
  // Don't question NAMBLA (North American Marlon Brando Look-Alikes)
  double **nambla_b = NULL;
  double ***nambla_w = NULL;
  for (int i = 0; i < net->layerCount; i++) {
    nambla_b[i] = (double *)calloc(net->layerSizes[i], sizeof(double));
    for (int j = 0; j < net->layerSizes[i]; j++) {
      nambla_b[i][j] = 0.0;
    }
  }
  for (int layer = 1; layer < net->layerCount; layer++) {
    nambla_w[layer] =
        (double **)calloc(net->layerSizes[layer], sizeof(double *));
    for (int node = 0; node < net->layerSizes[layer]; node++) {
      nambla_w[layer][node] =
          (double *)calloc(net->layerSizes[layer - 1], sizeof(double));
      for (int w = 0; w < net->layerSizes[layer - 1]; w++) {
        nambla_w[layer][node][w] = 0.0;
      }
    }
  }
}
