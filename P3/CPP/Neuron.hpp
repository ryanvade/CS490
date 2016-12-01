#ifndef NEURON
#define NEURON

#include "CachedInputNeuron.hpp"

class Neuron: public CachedInputNeuron {
private:
  CachedInputNeuron* inputs;
  double* weights;
public:
  Neuron(CachedInputNeuron* inputs)
  {
    this.inputs = inputs;
  }

  ~Neuron()
  {
    // TODO
  }

  double weightedSumation()
  {
    // TODO
    return 0.0;
  }

  double activationFunction()
  {
    // TODO
    return 0.0;
  }
};
#endif
