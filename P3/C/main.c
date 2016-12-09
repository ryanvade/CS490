#include "network.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  double alpha = 0.5;
  double inputs[6] = {0, 1, 2, 3, 4, 5};
  double expectedOutputs[3] = {0, 1, 2};
  int layerSizes[4] = {6, 4, 4, 3};
  Network net;
  initializeNetwork(&net, 2, &layerSizes[0]);
  backPropagate(&net, &inputs[0], &expectedOutputs[0], alpha);
  return 0;
}
