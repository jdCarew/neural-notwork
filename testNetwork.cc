// Purpose: Create gene sample pool for debugging, eventually will include ability to set all the key flags
//
// Command syntax:
//   $ ./neuralNotwork
//
// Examples:
#include "species.h"

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
    int inputSize=1;
    int outputSize=1;
    int layerSizes[]={inputSize,3,outputSize};
    int numLayers=3;
    unsigned int numNetworks=9;
    unsigned int numGenerations=15;

    vector<vector<double> > testData;
    vector<vector<double> > expectedResults;
    for (unsigned int i=0; i<numGenerations; i++){
        testData.push_back(vector<double>(inputSize,1));
        expectedResults.push_back(vector<double>(outputSize,1));
    }

    Species spec(numNetworks,numLayers,layerSizes,numGenerations);
    spec.verbose(1);
    spec.update(testData,expectedResults);

}// main
