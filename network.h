//The network implementation contains a bunch of neurons that do a real shit job of interacting

#ifndef __NETWORK__
#define __NETWORK__

#include "chromosome.h"

class Network{
    unsigned int numLayers;
    unsigned int *sizes;
    unsigned int *biases;
    unsigned int *weights;

    public:

    Network(unsigned int layers, unsigned int *layerSizes);
    ~Network();
};

#endif
