#include "Network.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Network net;
  int layerSizes[4] = {6, 4, 4, 3};
  initializeNetwork(&net, 2, (int *)layerSizes);
  double inputs[6] = {0, 1, 2, 3, 4, 5};
  printf("%d \n", net.layerSizes[0]);
  for (int i = 0; i < net.layerSizes[0]; i++) {
    net.layers[0][i] = inputs[i];
  }
  printf("\n\nBiases: \n");
  for (int i = 0; i < net.layerCount; i++) {
    for (int j = 0; j < net.layerSizes[i]; j++) {
      printf("%f ", net.biases[i][j]);
    }
    printf("\n ");
  }
  printf("\n\nLayers: \n");
  for (int i = 0; i < net.layerCount; i++) {
    for (int j = 0; j < net.layerSizes[i]; j++) {
      printf("%f ", net.layers[i][j]);
    }
    printf("\n ");
  }
  printf("\n\n");
  printf("\n\nWeights: \n");
  for (int i = 1; i < net.layerCount; i++) {
    for (int j = 0; j < net.layerSizes[i]; j++) {
      for (int k = 0; k < net.layerSizes[i - 1]; k++) {
        printf("%f ", net.weights[i][j][k]);
      }
    }
    printf("\n ");
  }
  printf("\n\n");
  double outputs[3] = {0, 1, 2};
  forwardPropogate(&net, (double *)inputs);
  printf("\n\nBiases: \n");
  for (int i = 0; i < net.layerCount; i++) {
    for (int j = 0; j < net.layerSizes[i]; j++) {
      printf("%f ", net.biases[i][j]);
    }
    printf("\n ");
  }
  printf("\n\nLayers: \n");
  for (int i = 0; i < net.layerCount; i++) {
    for (int j = 0; j < net.layerSizes[i]; j++) {
      printf("%f ", net.layers[i][j]);
    }
    printf("\n ");
  }
  printf("\n\nWeights: \n");
  for (int i = 1; i < net.layerCount; i++) {
    for (int j = 0; j < net.layerSizes[i]; j++) {
      for (int k = 0; k < net.layerSizes[i - 1]; k++) {
        printf("%f ", net.weights[i][j][k]);
      }
    }
    printf("\n ");
  }
  printf("\n\n");

  return 0;
}
