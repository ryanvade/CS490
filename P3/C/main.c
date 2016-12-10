#include "network.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  double alpha = 0.5;
  double inputs[6] = {(double)rand(), (double)rand(), (double)rand(),
                      (double)rand(), (double)rand(), (double)rand()};
  double expectedOutputs[3] = {(double)rand(), (double)rand(), (double)rand()};
  int layerSizes[4] = {6, 4, 4, 3};
  Network net;
  initializeNetwork(&net, 2, &layerSizes[0]);
  backPropagate(&net, &inputs[0], &expectedOutputs[0], alpha);
  double *outputs = net.layers[net.layerCount - 1];
  printf("\n\n");
  for (int i = 0; i < 3; i++)
    printf("%f ", outputs[i]);
  printf("\n");

  forwardPropagate(&net, &inputs[0], &outputs[0]);
  printf("\n\n");
  for (int i = 0; i < 3; i++)
    printf("%f ", outputs[i]);
  printf("\n");

  inputs[0] = (double)rand();
  inputs[1] = (double)rand();
  inputs[2] = (double)rand();
  inputs[3] = (double)rand();
  inputs[4] = (double)rand();
  inputs[5] = (double)rand();

  forwardPropagate(&net, &inputs[0], &outputs[0]);
  printf("\n\n");
  for (int i = 0; i < 3; i++)
    printf("%f ", outputs[i]);
  printf("\n");

  return 0;
}
