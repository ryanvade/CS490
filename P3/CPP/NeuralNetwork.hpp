#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include "Neuron.hpp"
#include "Synapse.hpp"

#include <stdio.h>
#include <stdlib.h>

class NeuralNetwork {
private:
  int numHidenLayers;
  int* neuronsPerLayer;
  int numInput;
  int numOutput;
  int epochs;
  Synapse** links;
  Neuron** network;

  void initializeNeurons()
  {
    // Allocation
    this.network = new (Neuron*)[this.numHidenLayers + 2];
    // Input
    this.network[0] = new (Neuron*)[this.numInput];
    for(int i = 0; i < this.numInput; i++)
    {
      this.network[0][i] = new Neuron();
    }
    // Output
    this.network[this.numHidenLayers + 1] = new (Neuron)[this.numOutput];
    for(int i = 0; i < this.numOutput; i++)
    {
      this.network[this.numHidenLayers + 1][i] = new Neuron();
    }
    // Hidden Layers
    for(int i = 1; i < this.numHidenLayers; i++)
    {
      this.network[i] = new (Neuron*)[this.neuronsPerLayer[i - 1]];
      for(int j = 0; j < this.neuronsPerLayer[i-1]; j++)
      {
        this.network[i][j] = new Neuron();
      }
    }

  }

  void initilizeSynapses()
  {
    this.links = new (Synapse*)[this.numHidenLayers + 2];
    for(int i = 0; i < this.numInput; i++)
    {
      // TODO
    }

    for(int i = 2; i < this.numHidenLayers - 1; i++)
    {
      // TODO
    }

    for(int k = 0; k < this.numOutput; k++)
    {
      // TODO
    }
  }

  void randomizeWeights()
  {
    // TODO
  }

  void destructNeurons()
  {
    // inputs
    for(int i = 0; i < this.numInput; i++)
    {
      delete(this.network[0][i]);
      this.network[0][i] = null;
    }
    // outputs
    for(int j = 0; j < this.numOutput; j++)
    {
      delete(this.network[this.numHidenLayers + 1][j]);
      this.numHidenLayers + 1][j] = null;
    }
    // hidden Layers
    for(int k = 1; k < this.numHidenLayers; k++)
    {
      for(int l = 0; l < this.neuronsPerLayer[k-1]; l++)
      {
        delete(this.network[k][l]);
        this.network[k][l] = null;
      }
    }
  }

  void destructSynapses()
  {
    // TODO
  }

  void normalizeInputs()
  {
    // TODO
  }

public:
  NeuralNetwork(int numHidenLayers, int* neuronsPerLayer, int numInput, int numOutput, int epochs)
  {
    this.numHidenLayers = numHidenLayers;
    this.neuronsPerLayer = neuronsPerLayer;
    this.numInput = numInput;
    this.numOutput = numOutput;
    this.epochs = epochs;

    initializeNeurons();
    initilizeSynapses();
    randomizeWeights();
  }

  ~NeuralNetwork()
  {
    destructNeurons();
    destructSynapses();
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
    double* outputs = new double[this.numOutput];
    for(int i = 0; i < this.numOutput; i++)
    {
      outputs[i] = this.network[][i].activationFunction(); // TODO
    }
    return outputs;
  }

};
#endif
