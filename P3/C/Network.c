#include "Network.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double sigmoidPrime(double x) { return pow(exp(-x) / ((1 + exp(-x))), 2); }

void initializeNetwork(Network *network, int numHiddenLayers, int *layerSizes) {
  network->layerCount = numHiddenLayers + 2;
  network->layerSizes = layerSizes;
  network->layers = (double **)calloc(numHiddenLayers + 2, sizeof(double *));
  network->weightedSums =
      (double **)calloc(numHiddenLayers + 2, sizeof(double *));
  network->biases = (double **)calloc(numHiddenLayers + 2, sizeof(double *));
  network->weights = (double ***)calloc(numHiddenLayers + 1, sizeof(double **));

  for (int i = 0; i < numHiddenLayers + 2; i++) {
    network->layers[i] = (double *)calloc(layerSizes[i], sizeof(double));
    network->weightedSums[i] = (double *)calloc(layerSizes[i], sizeof(double));
    network->biases[i] = (double *)calloc(layerSizes[i], sizeof(double));
    for (int j = 0; j < layerSizes[i]; j++) {
      network->layers[i][j] = 0.0;
      network->weightedSums[i][j] = 0.0;
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

void forwardPropagate(Network *network, double *inputs, double *outputs) {
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
      network->weightedSums[l][n] =
          dotProduct(network->weights[l][n], network->layers[l - 1],
                     network->layerSizes[l - 1]) +
          network->biases[l][n];
      network->layers[l][n] = network->weightedSums[l][n];
    }
  }

  // Copy the outputs into the buffer, if it was provided
  if (outputs != NULL)
    for (int o = 0; o < network->layerSizes[network->layerCount - 1]; o++)
      outputs[o] = network->layers[network->layerCount - 1][o];
}

void backPropagate(Network *net, double *inputs, double *expectedOutputs) {
  forwardPropagate(net, inputs, NULL);
  // actual outputs from the network
  double *outputs = net->layers[net->layerCount - 1];
  // Don't question NAMBLA (North American Marlon Brando Look-Alikes)
  double **nambla_b = (double **)calloc(net->layerCount, sizeof(double *));
  double **nambla_w = (double **)calloc(net->layerCount, sizeof(double *));

  // Calculate the gradient of the weights and bias for each node
  double *deltas = NULL;

  // sums is vector of weighted sums of node inputs
  double **sums = (double **)calloc(net->layerCount, sizeof(double *));
  double *sigmoids =
      (double *)calloc(net->layerSizes[net->layerCount - 1], sizeof(double));
  for (int i = 0; i < net->layerCount; i++) {
    sums[i] = (double *)calloc(net->layerSizes[i], sizeof(double *));
  }

  // For every output node
  for (int outN = 0; outN < net->layerSizes[net->layerCount - 1]; outN++) {

    // Caclulate the weighted sum of this nodes inputs
    sums[net->layerCount - 1][outN] =
        dotProduct(net->weights[net->layerCount - 1][outN],
                   net->layers[net->layerCount - 1],
                   net->layerSizes[net->layerCount - 1]) +
        net->biases[net->layerCount - 1][outN];

    sigmoids[outN] = sigmoidPrime(sums[net->layerCount - 1][outN]);
  }
  deltas = hadamardMul(
      vectorSub(outputs, expectedOutputs, net->layerSizes[net->layerCount - 1]),
      sigmoids, net->layerCount - 1);
  nambla_b[net->layerCount - 1] = deltas;
  nambla_w[net->layerCount - 1] =
      hadamardMul(deltas, net->layers[net->layerCount - 2],
                  net->layerSizes[net->layerCount - 2]);

  sigmoids = NULL;
  double d;
  for (int i = net->layerCount - 2; i > 0; i--) {
    for (int n = 0; n < net->layerSizes[i]; n++) {
      sigmoids[n] = sigmoidPrime(net->weightedSums[i][n]);
    }
    d = dotProduct(deltas, net->weights[i][]);
    deltas = vectorSub(deltas, d, net->layerSizes[i + 1]);
  }
}
