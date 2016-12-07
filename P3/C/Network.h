#ifndef NETWORK_H
#define NETWORK_H
typedef struct {
  int layerCount;
  int *layerSizes;
  double **layers;
  double **biases;
  double ***weights;
} Network;

#endif
