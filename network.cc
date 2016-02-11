#include "network.h"

Network::Network(unsigned int layers, unsigned int *layerSizes){
    numLayers=layers;
    sizes=new unsigned int[numLayers];
    for (unsigned int i=0; i<numLayers; i++){
        sizes[i]=layerSizes[i];
    }
    biases=new unsigned int[numLayers];
    for (unsigned int i=0; i<numLayers; i++){
//        biases[i]=;//want a gaussian distribution
    }
    weights=new unsigned int[numLayers];
    for (unsigned int i=0; i<numLayers; i++){
//        weights[i]=;//want a gaussian distribution
    }
}

Network::~Network(){
    delete []sizes;
    delete []biases;
    delete []weights;
}

