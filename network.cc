#include "network.h"

Neuron::Neuron(int numberOfInputs):numInputs(numberOfInputs){
    for(int i=0; i<numInputs; i++){
        weights.push_back(RandFloat());
    }
    bias=RandFloat();
}

void Neuron::printNeuron(){
	for(int i=0; i<numInputs; i++){
		std::cout<<"Weight at "<<i<<": "<<weights[i]<<std::endl;
	}
	std::cout<<"Bias: "<<bias<<std::endl;

}

Layer::Layer(int numberOfNeurons, int numberOfInputs):numNeurons(numberOfNeurons){
    for(int i=0; i<numNeurons; i++){
        neurons.push_back(Neuron(numberOfInputs));
    }
}

void Layer::printLayer(){
	for(int i=0; i<numNeurons; i++){
		std::cout<<"Neuron #"<<i<<":"<<std::endl;
		neurons[i].printNeuron();
	}
}

Network::Network(int numberOfLayers, int *layerSizes){
	numInputs=layerSizes[0];
	numLayers=numberOfLayers;
	numberFinalOutputs=layerSizes[numLayers-1];
	layers.push_back(Layer(numInputs,1));//first nodes all take one input, will be fed specially
	for(int i=1; i<numberOfLayers; i++){
		layers.push_back(Layer(layerSizes[i],layerSizes[i-1]));
	}
}

void Network::printNetwork(){
	for(int i=0; i<numLayers; i++){
		std::cout<<"Layer #"<<i<<":"<<std::endl;
		layers[i].printLayer();
	}
}

Network::~Network(){
}

