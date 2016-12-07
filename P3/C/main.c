#include "Network.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  double inputs[6] = {0, 1, 2, 3, 4, 5};
  double **inputsT = transpose((double *)inputs, 6, 1);
  for (int i = 0; i < 6; i++) {
    printf("%f ", inputs[i]);
  }
  printf("\n\n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 1; j++) {
      printf("%f ", inputsT[i][j]);
    }
    printf("\n");
  }

  double **i2 = (double **)calloc(6, sizeof(double *));
  for (int i = 0; i < 6; i++) {
    i2[i] = (double *)calloc(6, sizeof(double *));
    for (int j = 0; j < 6; j++) {
      i2[i][j] = rand();
    }
  }

  printf("\n\n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      printf("%f ", i2[i][j]);
    }
    printf("\n");
  }
  double **i2T = transpose2D(i2, 6, 6);
  printf("\n\n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      printf("%f ", i2T[i][j]);
    }
    printf("\n");
  }

  double ***i3 = (double ***)calloc(6, sizeof(double **));
  for (int i = 0; i < 6; i++) {
    i3[i] = (double **)calloc(6, sizeof(double *));
    for (int j = 0; j < 6; j++) {
      i3[i][j] = (double *)calloc(6, sizeof(double));
      for (int k = 0; k < 6; k++) {
        i3[i][j][k] = rand();
      }
    }
  }

  printf("\n\n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 6; k++) {
        printf("%f ", i3[i][j][k]);
      }
    }
  }
  printf("\n");

  double ***i3T = transpose3D(i3, 6, 6, 6);
  printf("\n\n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 6; k++) {
        printf("%f ", i3T[i][j][k]);
      }
    }
  }
  printf("\n");
  // Network net;
  // int layerSizes[4] = {6, 4, 4, 3};
  // initializeNetwork(&net, 2, (int *)layerSizes);
  // double inputs[6] = {0, 1, 2, 3, 4, 5};
  // printf("%d \n", net.layerSizes[0]);
  // for (int i = 0; i < net.layerSizes[0]; i++) {
  //   net.layers[0][i] = inputs[i];
  // }
  // printf("\n\nBiases: \n");
  // for (int i = 0; i < net.layerCount; i++) {
  //   for (int j = 0; j < net.layerSizes[i]; j++) {
  //     printf("%f ", net.biases[i][j]);
  //   }
  //   printf("\n ");
  // }
  // printf("\n\nLayers: \n");
  // for (int i = 0; i < net.layerCount; i++) {
  //   for (int j = 0; j < net.layerSizes[i]; j++) {
  //     printf("%f ", net.layers[i][j]);
  //   }
  //   printf("\n ");
  // }
  // printf("\n\n");
  // printf("\n\nWeights: \n");
  // for (int i = 1; i < net.layerCount; i++) {
  //   for (int j = 0; j < net.layerSizes[i]; j++) {
  //     for (int k = 0; k < net.layerSizes[i - 1]; k++) {
  //       printf("%f ", net.weights[i][j][k]);
  //     }
  //   }
  //   printf("\n ");
  // }
  // printf("\n\n");
  // double outputs[3] = {0, 1, 2};
  // forwardPropogate(&net, (double *)inputs);
  // printf("\n\nBiases: \n");
  // for (int i = 0; i < net.layerCount; i++) {
  //   for (int j = 0; j < net.layerSizes[i]; j++) {
  //     printf("%f ", net.biases[i][j]);
  //   }
  //   printf("\n ");
  // }
  // printf("\n\nLayers: \n");
  // for (int i = 0; i < net.layerCount; i++) {
  //   for (int j = 0; j < net.layerSizes[i]; j++) {
  //     printf("%f ", net.layers[i][j]);
  //   }
  //   printf("\n ");
  // }
  // printf("\n\nWeights: \n");
  // for (int i = 1; i < net.layerCount; i++) {
  //   for (int j = 0; j < net.layerSizes[i]; j++) {
  //     for (int k = 0; k < net.layerSizes[i - 1]; k++) {
  //       printf("%f ", net.weights[i][j][k]);
  //     }
  //   }
  //   printf("\n ");
  // }
  // printf("\n\n");

  return 0;
}
