import numpy as np

class Node(object):
    def __init__(self, weights, activationFunction):
        self.weights = weights
        self.activationFunction = activationFunction
        self.z = 0.0
        self.a = 0.0

    def update(self, input):
        self.z = 0.0
        if self.weights is not None:
            for w in self.weights:
                self.z += w * input
            self.a = self.activationFunction(self.z)
        else:
            self.z = input
            self.a = self.activationFunction(self.z)

class Network(object):
  def __init__(self, numberInputNodes, numberHiddenLayers, numberNodesPerHiddenLayer, numberOutputNodes, activationFunction):
      self.numberInputNodes = numberInputNodes
      self.numberHiddenLayers = numberHiddenLayers
      self.numberNodesPerHiddenLayer = numberNodesPerHiddenLayer
      self.numberOutputNodes = numberOutputNodes
      self.layers = [][]

      for i in range(self.numberInputNodes):
          self.layers[0][i] = Node(None, self.activationFunction)

      weights = np.random.randn(self.numberInputNodes, self.numberNodesPerHiddenLayer[0])
      for hl in range(1, self.hiddenLayerSize - 1):
          for hn in range(self.numberNodesPerHiddenLayer[hl]):
              self.layers[hl][hn] = Node(weights, self.activationFunction)
              weights = np.random.randn(self.numberNodesPerHiddenLayer[hl + 1])

       weights = np.random.randn(self.numberNodesPerHiddenLayer[self.numberHiddenLayers], self.numberOutputNodes)
       for o in range(self.numberOutputNodes):
           self.layers[self.numberHiddenLayers][o] = Node(weights, self.activationFunction)

  def forwardPropogate(self, inputValues):
      for i in range(self.numberInputNodes):
          self.layers[0][i].update(inputValues[i])

      for hl in range(self.numberHiddenLayers):
          for hn in range(self.numberNodesPerHiddenLayer[hl]):
              self.layers[hl][hn].update(self.layers[hl-1][hn])

       for on in range(self.numberOutputNodes):
           for hn in range(self.numberNodesPerHiddenLayer[])
           self.layers[self.numberHiddenLayers][on].update(self.layers[])

class RobotTrainer(object):
    def __init__(self, network):
        self.network = network


    def train(self, trainingInput, trainingOutput):
        self.trainingInput = trainingInput
        self trainingOutput = trainingOutput
