#ifndef NETWORK_H
#define NETWORK_H
typedef struct {
  int layerCount;
  int *layerSizes;
  double **layers;
  double **biases;
  double ***weights;
} Network;

void initializeNetwork(Network *network, int numHiddenLayers, int *layerSizes);
void forwardPropagate(Network *network, double *inputs, double *outputs);

#endif
