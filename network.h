//The neural network implementation contains a bunch of neurons that do a real shit job of interacting

#ifndef __NETWORK__
#define __NETWORK__

#include <vector>
#include <math.h>
#include <cstdlib>
#include <numeric>
#include <assert.h>
#include <iostream>

#define mutationRate (0.55)

inline double RandFloat(){return (rand())/(RAND_MAX+1.0);}
inline double RandFloat(double limit){return (rand())/(RAND_MAX/limit);}
inline double RandDouble(){return (rand());}
inline int    RandInt(int x,int y) {return rand()%(y-x+1)+x;}
inline double RandomClamped()      {return RandFloat() - RandFloat();}

inline double max( double a, double b) { return ((a<b)?b:a); }
inline double min( double a, double b) { return ((a>b)?b:a); }

struct Neuron{
    int numInputs;
    std::vector<double> weights;
    double bias;
    Neuron(int numberOfInputs);

    //This is used for an early version of the weights evolve that would merge two
    Neuron(Neuron n1, Neuron n2);
    double evaluate(std::vector<double>inputs);
    
    void develop();

    void printNeuron();
    ~Neuron();
};

struct Layer{
    int numNeurons;
    std::vector<struct Neuron> neurons;
    Layer(int numberOfNeurons, int numberOfInputs);

    //Early version that would merge two 
    Layer(Layer L1, Layer L2);
    void develop();

    std::vector<double> evaluate(std::vector<double>inputs);

    void printLayer();   
    ~Layer();
};

class Network{
    int numInputs;
    int numLayers;
    int numberFinalOutputs;
    double fitness;
    std::vector<struct Layer> layers;
    public:
    double getFitness();
    void setFitness(double fit);
    //number of layers, than each layer has a number of inputs to each neuron, 0th is input
    Network(int numberOfLayers, int *sizePerLayer);

    //this early version would merge two networks for shared fitness, not very effective
    Network(Network N1, Network N2);

    std::vector<double> evaluate(double *inputs);
    std::vector<double> evaluate(std::vector<double>inputs);
    void printNetwork();
    ~Network();
};


#endif
