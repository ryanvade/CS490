#include "network.h"
#include "vector.h"
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readIntoBuffer(double *out, size_t count, FILE *file) {
    char buffer[20];
    int chars = 0;
    int data = 0;

    while(fread(buffer+chars, 1,1, file) && data < count) {
        if(isspace(buffer[chars]) && chars > 0) {
            buffer[chars] = '\0';
            out[data] = strtod(buffer, NULL);
            printf("Read: %f\n", out[data]);
            data++;
            chars = -1;
        }
        chars++;
    }
    return data;
}
int main() {
  srand(time(NULL));
  double alpha = 0.5;
  double inputs[6];
  double expectedOutputs[3];
  int layerSizes[4] = {6, 4, 4, 3};
  Network net;
  initializeNetwork(&net, 2, &layerSizes[0]);

  int epochs = 50;
  FILE *trainingData = fopen("trainingData", "r");
  for(int i = 0; i < epochs; i++) {
      printf("Reading epoch %d of %d\n", i + 1, epochs);

      readIntoBuffer(inputs, 6, trainingData);
      readIntoBuffer(expectedOutputs, 3, trainingData);

      printf("Backpropagating epoch %d of %d\n", i + 1, epochs);
      backPropagate(&net, &inputs[0], &expectedOutputs[0], alpha);
      printf("Finshed epoch %d of %d\n", i + 1, epochs);
  }
  printWeights(&net);

  double *outputs = net.layers[net.layerCount - 1];
  forwardPropagate(&net, &inputs[0], &outputs[0]);

  printf("\n\nInputs:\n");
  for(int i = 0; i < 6; i++)
    printf("%f ", inputs[i]);
  printf("\n\nOutputs:\n");
  for(int i = 0; i < 3; i++)
    printf("%f ", outputs[i]);
  printf("\n");

  /*
  backPropagate(&net, &inputs[0], &expectedOutputs[0], alpha);
  double *outputs = net.layers[net.layerCount - 1];
  forwardPropagate(&net, &inputs[0], &outputs[0]);
  */

  return 0;
}
