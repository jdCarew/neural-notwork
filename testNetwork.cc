// Purpose: Create gene sample pool
//
// Command syntax:
//   $ ./notwork
//
// Examples:
#include "chromosome.h"
#include "network.h"

#define NOTRANDOMFITNESS
using namespace std;

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]<<endl;
    exit( EXIT_FAILURE );
}

#ifdef RANDOMFITNESS
unsigned int calculateFitness(unsigned long chromosome){
    return 4;//chosen by random dice roll, guaranteed to be random
}
#else
unsigned int calculateFitness(unsigned long chromosome){
    return (unsigned int)(chromosome>>60);
}
#endif

void usage(){
    cout<<"notwork"<<endl;
}

int main( int argc, char *argv[] ) {
	/*The first layer is implied input layer.
	   Example: the first passed layer is size 5, then there will be 5 inputs passed to each neuron in that one
	*/
    int layerSizes[]={1,1};
    int numLayers=2;
    double sampleinputs[]={1.0,5.4};
    Network network(numLayers,layerSizes);
    Network network2(numLayers,layerSizes);
    network.printNetwork();
    network2.printNetwork();
    network.fitness=2.0;
    network2.fitness=2.0;
    vector<double> results=network.evaluate(sampleinputs);
    for(vector<double>::const_iterator it=results.begin(); it!=results.end();++it){
    	cout<<*it<<" ";
    }
    cout<<endl;

    Network N3(network,network2);
    N3.printNetwork();
} // main
