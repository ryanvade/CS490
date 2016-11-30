#ifndef SYNAPSE
#define SYNAPSE

#include "Neuron.hpp"

class Synapse {
private:
  Neuron* A;
  Neuron* B;
  int weight;
public:

  Synapse(Neuron* A, Neuron* B, int weight)
  {
    this->A = A;
    this->B = B;
    this->weight = weight;
  }

  ~Synapse()
  {
    // TODO
  }

  int getWeight()
  {
    return this->weight;
  }

  void setWeight(int weight)
  {
    this->weight = weight;
  }

  Neuron* getA()
  {
    return this->A;
  }

  Neuron* getB()
  {
    return this->B;
  }

};
#endif
