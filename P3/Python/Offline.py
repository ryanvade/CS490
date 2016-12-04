import numpy as np
from scipy import optimize

class Network(object):
    def __init__(self):
        self.inputLayerSize = 8
        self.outputLayerSize = 2
        self.hiddenLayerSize = 4

        self.W0 = np.random.randn(self.inputLayerSize, self.hiddenLayerSize)
        self.W1 = np.random.randn(self.hiddenLayerSize, self.hiddenLayerSize)
        self.W2 = np.random.randn(self.hiddenLayerSize, self.hiddenLayerSize)
        self.W3 = np.random.randn(self.hiddenLayerSize, self.outputLayerSize)

    def forwardPropogate(self, inputValues):
        # z0 = x0*W0
        self.z0 = np.dot(inputValues, self.W0)
        # a0 = activationFunction(z0)
        self.a0 = self.sigmoid(self.z0)
        # z1 = x1*w1
        self.z1 = np.dot(self.a0, self.W1)
        # a1 = activationFunction(z1)
        self.a1 = self.sigmoid(self.z1)
        # z2 = x2*w2
        self.z2 = np.dot(self.a1, self.W2)
        # a2 = activationFunction(z2)
        self.a2 = self.sigmoid(self.z2)
        #z3 = x3 * w3
        self.z3 = np.dot(self.a2, self.W3)
        #a3 (output Estimate) = activationFunction(z3)
        self.a3 = self.sigmoid(self.z3)
        outputEstimate = self.sigmoid(self.z3)
        return outputEstimate

    def sigmoid(self, Z):
        return 1/(1+np.exp(-Z))

    def sigmoidPrime(self, Z):
        return np.exp(-Z)/((1+np.exp(-Z))**2)

    def cost(self, inputValues, output):
        self.outputEstimate = self.forwardPropogate(inputValues)
        # Cost = (1/2 * # inputs (# training samples)) * SUM OF (h(x) - output)^2
        # h(x) in this case is the actual output
        cost = (1/ (2 * self.inputLayerSize)) * sum((output - self.outputEstimate)**2)
        return cost

    def costPrime(self, inputValues, output):
        self.outputEstimate = self.forwardPropogate(inputValues)

        # error
        delta4 = np.multiply(-(output - self.outputEstimate), self.sigmoidPrime(self.z3))
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
        j = self.network.cost(self.inputValues, self.output)
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
        _res = optimize.minimize(self.costFunction, weights, jac=True, method='BFGS', \
                                 args=(inputValues, output), options=options, callback=self.callback)

        self.network.setWeights(_res.x)
        self.optimizationResults = _res


trainingInput = np.array(([0,1, 2, 3, 4, 5, 6, 7], [8, 9, 10, 11, 12, 13,14, 15], [16, 17, 18, 19, 20, 21, 22, 23]), dtype=float)
trainingOutput = np.array(([0,1], [2,3], [4, 5]), dtype=float)

# trainingInput = trainingInput/np.amax(trainingInput, axis=0)
# trainingOutput = trainingOutput/5

network = Network()
robotTrainer = RobotTrainer(network)
robotTrainer.run(trainingInput, trainingOutput)
