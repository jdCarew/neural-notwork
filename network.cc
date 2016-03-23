#include "network.h"

Neuron::Neuron(int numberOfInputs):numInputs(numberOfInputs){
    for(int i=0; i<numInputs; i++){
        weights.push_back(RandFloat());
    }
    bias=RandFloat();
}

Neuron::Neuron(Neuron n1, Neuron n2){
	assert(n1.numInputs==n2.numInputs);
	numInputs=n1.numInputs;

	int split=RandInt(0,numInputs);

	for(int i=0; i<split; i++){
		weights.push_back(n1.weights[i]);
	}
	for(int i=split; i<numInputs; i++){
		weights.push_back(n2.weights[i]);
	}
	for(std::vector<double>::iterator it=weights.begin(); it!=weights.end(); ++it){
		if(RandFloat()>mutationRate){
			(*it)*=RandInt(95,105)/100.0; //perturb by 5%
		}
	}
	if (split*2>numInputs){
		bias=n1.bias;
	}else{
		bias=n2.bias;
	}
}

double Neuron::evaluate(std::vector<double> inputs){
	assert(weights.size()==inputs.size());
	return 1.0/(1.0+exp(-1.0*inner_product(weights.begin(),weights.end(),inputs.begin(),bias)));
}

Neuron::~Neuron(){
	weights.clear();
}

void Neuron::printNeuron(){
	for(int i=0; i<numInputs; i++){
		std::cout<<"\t\tWeight at "<<i<<": "<<weights[i]<<std::endl;
	}
	std::cout<<"\t  Bias: "<<bias<<std::endl;
}

Layer::Layer(int numberOfNeurons, int numberOfInputs):numNeurons(numberOfNeurons){
    for(int i=0; i<numNeurons; i++){
        neurons.push_back(Neuron(numberOfInputs));
    }
}

Layer::Layer(Layer L1, Layer L2){
	assert(L1.numNeurons==L2.numNeurons);
	numNeurons=L1.numNeurons;
	for (int i=0; i<L1.numNeurons; i++){
		neurons.push_back(Neuron(L1.neurons[i],L2.neurons[i]));
	}
}

std::vector<double> Layer::evaluate(std::vector<double> inputs){
	std::vector<double>outputs;
	/*this is probably a great time to multithread the application
		Difficulty: needs to be thread safe push_backs, so either need to lock it, or they can return by a reference, or need to use futures.
		Probable best solution is reference, so create an array and then pass each a pointer to it's spot in the array,
		then join all threads and copy array to the vector. Will probably be worth it for 100 input neurons
	*/
	for (std::vector<Neuron>::iterator it = neurons.begin() ; it != neurons.end(); ++it){
		outputs.push_back((*it).evaluate(inputs));
	}
	return outputs;
}

Layer::~Layer(){
	neurons.clear();
}

void Layer::printLayer(){
	for(int i=0; i<numNeurons; i++){
		std::cout<<"\tNeuron #"<<i<<":"<<std::endl;
		neurons[i].printNeuron();
	}
}

//called on the first generation to build a random set
Network::Network(int numberOfLayers, int *layerSizes){
	numInputs=layerSizes[0];
	numLayers=numberOfLayers;
	numberFinalOutputs=layerSizes[numLayers-1];
	fitness=0;
	layers.push_back(Layer(numInputs,numInputs));//first nodes all take one input, will be fed specially
	for(int i=1; i<numberOfLayers; i++){
		layers.push_back(Layer(layerSizes[i],layerSizes[i-1]));
	}
}

Network::Network(Network N1, Network N2){
	assert(N1.numInputs==N2.numInputs && N1.numLayers == N2.numLayers);
	numInputs=N1.numInputs;
	numLayers=N1.numLayers;
	numberFinalOutputs=N1.numberFinalOutputs;
	fitness=0;
	for(int i=0; i<numLayers; i++){
		layers.push_back(Layer(N1.layers[i],N2.layers[i]));
	}
}

std::vector<double> Network::evaluate(double * inputs){
	std::vector<double> myinputs(inputs, inputs+numInputs);
	for (std::vector<Layer>::iterator it=layers.begin(); it!=layers.end(); ++it){
		myinputs=(*it).evaluate(myinputs);
	}
	return myinputs;
}

std::vector<double> Network::evaluate(std::vector<double> inputs){
	for (std::vector<Layer>::iterator it=layers.begin(); it!=layers.end(); ++it){
		inputs=(*it).evaluate(inputs);
	}
	return inputs;
}

void Network::printNetwork(){
	std::cout<<"Fitness: "<<fitness<<std::endl;
	for(int i=0; i<numLayers; i++){
		std::cout<<"Layer #"<<i<<":"<<std::endl;
		layers[i].printLayer();
	}
}

Network::~Network(){
	layers.clear();
}

double Network::getFitness(){
	return fitness;
}

void Network::setFitness(double fit){
	fitness=fit;
	return;
}