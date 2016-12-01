#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include "CachedInputNeuron.hpp"
#include "Neuron.hpp"
#include "Output.hpp"

#include <stdio.h>
#include <stdlib.h>

class NeuralNetwork {
private:
  int numHidenLayers;
  int* neuronsPerLayer;
  int numInput;
  int numOutput;
  int epochs;

  CachedInputNeuron* layers;
  Output* outputs;



  void initializeNeurons()
  {

  }


  void randomizeWeights()
  {
    // TODO
  }

  void destructNeurons()
  {

  }

  void normalizeInputs()
  {
    // TODO
  }

public:
  NeuralNetwork(int numHidenLayers, int* neuronsPerLayer, int numInput, int numOutput, int epochs)
  {
    this->numHidenLayers = numHidenLayers;
    this->neuronsPerLayer = neuronsPerLayer;
    this->numInput = numInput;
    this->numOutput = numOutput;
    this->epochs = epochs;

    initializeNeurons();
    randomizeWeights();
  }

  ~NeuralNetwork()
  {
    destructNeurons();
  }

  void loadWeightsFromFile()
  {
    // TODO
  }

  void run()
  {
    // TODO
  }

  double* outputValues()
  {
    // TODO
    return 0.0;
  }

};
#endif
