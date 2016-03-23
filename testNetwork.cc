// Purpose: Create gene sample pool
//
// Command syntax:
//   $ ./notwork
//
// Examples:
#include "species.h"

#define NOTRANDOMFITNESS
using namespace std;

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]<<endl;
    exit( EXIT_FAILURE );
}

void usage(){
    cout<<"notwork"<<endl;
}

int main( int argc, char *argv[] ) {
    srand(time(0));
	/*The first layer is implied input layer.
	   Example: the first passed layer is size 5, then there will be 5 inputs passed to each neuron in that one
	*/
    int layerSizes[]={4,4};
    int numLayers=2;
    unsigned int numNetworks=40;

    Species spec(numNetworks,numLayers,layerSizes,15);

    spec.update();

}// main
