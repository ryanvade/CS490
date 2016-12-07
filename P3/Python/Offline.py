import numpy as np
from scipy import optimize

class Network(object):
    def __init__(self, inputLayerSize, outputLayerSize, hiddenLayerSize, numberHiddenLayers):
        self.inputLayerSize = inputLayerSize
        self.outputLayerSize = outputLayerSize
        self.hiddenLayerSize = hiddenLayerSize
        self.numberHiddenLayers = numberHiddenLayers
        self.weights = []
        self.biases = []

        self.sizes = [self.inputLayerSize]
        for l in range(self.numberHiddenLayers):
            self.sizes.append(self.hiddenLayerSize)
        self.sizes.append(self.outputLayerSize)

        for y in self.sizes[1:]:
            self.biases.append(np.random.randn(y, 1))

        for x, y in zip(self.sizes[:-1], self.sizes[1:]):
            self.weights.append(np.random.randn(y, x))

    def forwardPropogate(self, inputValues):
        for b, w in zip(self.biases, self.weights):
            a = self.sigmoid(np.dot(w, inputValues)+b)
        return a

    def sigmoid(self, Z):
        return 1/(1+np.exp(-Z))

    def sigmoidPrime(self, Z):
        return np.exp(-Z)/((1+np.exp(-Z))**2)

    def cost(self, inputValues, output):
        print("input", inputValues)
        print("output", output)
        self.outputEstimate = self.forwardPropogate(inputValues)
        # Cost = (1/2 * # inputs (# training samples)) * SUM OF (h(x) - output)^2
        # h(x) in this case is the actual output
        cost = (1/ (2 * self.inputLayerSize)) * sum((output - self.outputEstimate)**2)
        return cost

    def costPrime(self, inputValues, output):
        self.outputEstimate = self.forwardPropogate(inputValues)

        # error
        delta4 = np.multiply(-(output - self.outputEstimate), self.sigmoidPrime(self.z3))
        print("Stuff", self.a2.T, delta4);
        # derivative of cost with respect to weight
        dcdw3 = np.dot(self.a2.T, delta4)

        delta3 = np.dot(delta4, self.W3.T) * self.sigmoidPrime(self.z2)
        dcdw2 = np.dot(self.a1.T, delta3)

        delta2 = np.dot(delta3, self.W2.T)  * self.sigmoidPrime(self.z1)
        dcdw1 = np.dot(self.a0.T, delta2)

        delta1 = np.dot(delta2, self.W1.T) * self.sigmoidPrime(self.z0)
        dcdw0 = np.dot(inputValues.T, delta1)

        return dcdw3, dcdw2, dcdw1, dcdw0

    def getWeights(self):
        return np.concatenate((self.W0.ravel(), self.W1.ravel(), self.W2.ravel(), self.W3.ravel()))
        #return [self.W0, self.W1, self.W2, self.W3]

    def setWeights(self, weights):
        W0_start = 0
        W0_end = self.inputLayerSize * self.hiddenLayerSize
        self.W0 = np.reshape(weights[W0_start:W0_end], (self.inputLayerSize , self.hiddenLayerSize))

        W1_end = W0_end + self.hiddenLayerSize*self.hiddenLayerSize
        self.W1 = np.reshape(weights[W0_end:W1_end], (self.hiddenLayerSize, self.hiddenLayerSize))

        W2_end = W1_end + self.hiddenLayerSize*self.hiddenLayerSize
        self.W2 = np.reshape(weights[W1_end:W2_end], (self.hiddenLayerSize, self.hiddenLayerSize))

        W3_end = W2_end + self.hiddenLayerSize*self.outputLayerSize
        self.W3 = np.reshape(weights[W2_end:W3_end], (self.hiddenLayerSize, self.outputLayerSize))
        # self.W0 = weights[0]
        # self.W1 = weights[1]
        # self.W2 = weights[2]
        # self.W3 = weights[3]

    def getGradients(self, inputValues, output):
        dcdw3, dcdw2, dcdw1, dcdw0 = self.costPrime(inputValues, output)
        return np.concatenate((dcdw3.ravel(), dcdw2.ravel(), dcdw1.ravel(), dcdw0.ravel()))

    def gradientChecking(self, inputValues, output):
        initialWeights = self.getWeights()
        numerical_gradients = np.zeros(initialWeights.shape)
        perturb_weights = np.zeros(initialWeights.shape)

        for w in range(len(initialWeights)):
            perturb_weights[w] = 1e-4 # very small number used for limit (cannot actually go to 0)

            self.setWeights(initialWeights + perturb_weights)
            error1 = self.cost(inputValues, output)

            self.setWeights(initialWeights - perturb_weights)
            error2 = self.cost(inputValues, output)

            numerical_gradients[p] = (error1 - error2) / (2 * e)

            perturb_weights[p] = 0 # set back to normal

        self.setWeights(initialWeights)
        return numerical_gradients

class RobotTrainer(object):
    def __init__(self, network):
        self.network = network

    def callback(self, weights):
        print("Callback: ")
        self.network.setWeights(weights)
        print("Weights:")
        print(weights)
        j = self.network.cost(self.inputValues[self.epoch], self.output[self.epoch])
        print("Cost:")
        print(j)
        self.cost.append(j)

    def costFunction(self, weights, inputValues, output):
        print("Cost Function: ")
        self.network.setWeights(weights)
        print("Weights:")
        print(weights)
        print("inputs: ")
        print(inputValues)
        print("outputs: ")
        print(output)
        cost = self.network.cost(inputValues, output)
        print("Cost:")
        print(cost)
        gradient = self.network.getGradients(inputValues, output)
        print("Gradient:")
        print(gradient)
        print("Exit Cost Function.")
        return cost, gradient

    def run(self, inputValues, output):
        #Make an internal variable for the callback function:
        self.inputValues = inputValues
        self.output = output

        #Make empty list to store costs:
        self.cost = []

        weights = self.network.getWeights()

        options = {'maxiter': 1, 'disp' : True}
        for epoch in range(len(inputValues)):
            self.epoch = epoch;
            _res = optimize.minimize(self.costFunction, weights, args=(inputValues[epoch], output[epoch]), method='BFGS', jac=True)
            self.network.setWeights(_res.x)

        print(_res.x)
