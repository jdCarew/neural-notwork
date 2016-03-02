//The neural network implementation contains a bunch of neurons that do a real shit job of interacting

#ifndef __NETWORK__
#define __NETWORK__

#include <vector>
#include <math.h>
#include <numeric>
#include <assert.h>

#include "chromosome.h"

#define learningBias = 0.1
//plan weight=oldweight-learningbias/samplesize*sum_j(delta CostXj/delta weight)

struct Neuron{
    int numInputs;
    std::vector<double> weights;
    double bias;
    Neuron(int numberOfInputs);
    Neuron(Neuron n1, double fit1, Neuron n2, double fit2);
    double evaluate(std::vector<double>inputs);
    
    void develop();

    void printNeuron();
    ~Neuron();
};

struct Layer{
    int numNeurons;
    std::vector<struct Neuron> neurons;
    Layer(int numberOfNeurons, int numberOfInputs);
    Layer(Layer L1, double fit1, Layer L2, double fit2);
    void develop();

    std::vector<double> evaluate(std::vector<double>inputs);

    void printLayer();   
    ~Layer();
};

class Network{
    int numInputs;
    int numLayers;
    int numberFinalOutputs;
    
    std::vector<struct Layer> layers;
    public:
    double fitness;
    //number of layers, than each layer has a number of inputs to each neuron, 0th is input
    Network(int numberOfLayers, int *sizePerLayer);
    Network(Network N1, Network N2);
    Network(int numberOfLayers, std::vector<struct layer> assignedLayers);

    std::vector<double> evaluate(double *inputs);

    void printNetwork();
    ~Network();
};


#endif
