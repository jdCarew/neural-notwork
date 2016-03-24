// Purpose: Create gene sample pool
//
// Command syntax:
//   $ ./notwork
//
// Examples:
#include "species.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]<<endl;
    exit( EXIT_FAILURE );
}

int main( int argc, char *argv[] ) {
    srand(time(0));

    int layerSizes[]={256,24,10};
    int numLayers=3;
    unsigned int numNetworks=40;
    unsigned int numGenerations=15;

    vector<vector<double> > testData;
    vector<vector<double> > expectedResults;
    
    fstream ifs("datasets/semeion.data", ifstream::in);
    string line;
    int i=0;
    vector<double> test;
    vector<double> expected;
    while (getline(ifs,line,' ')){
        double val;

        istringstream(line) >> val;
        if(i++<256){
            test.push_back(val);
        }else{
            expected.push_back(val);
        }
        
        if (i>=266){
            i=0;
            testData.push_back(test);
            expectedResults.push_back(expected);
            test.clear();
            expected.clear();    
        }
    }   

    Species spec(numNetworks,numLayers,layerSizes,numGenerations);

    spec.update(testData,expectedResults);

}// main
