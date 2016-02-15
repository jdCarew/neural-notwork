//The neural network implementation contains a bunch of neurons that do a real shit job of interacting

#ifndef __NETWORK__
#define __NETWORK__

#include <vector>
#include <math.h>

#include "chromosome.h"

struct Neuron{
    int numInputs;
    std::vector<double> weights;
    double bias;
    Neuron(int numberOfInputs);
    void printNeuron();
};

struct Layer{
    int numNeurons;
    std::vector<struct Neuron> neurons;
    Layer(int numberOfNeurons, int numberOfInputs);
    void printLayer();   
};

class Network{
    int numInputs;
    int numLayers;
    int numberFinalOutputs;
    std::vector<struct Layer> layers;
    public:

    //number of layers, than each layer has a number of inputs to each neuron, 0th is input
    Network(int numberOfLayers, int *sizePerLayer);

    void printNetwork();
    ~Network();
};

#endif
