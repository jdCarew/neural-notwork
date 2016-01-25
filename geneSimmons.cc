// Purpose: Create gene sample pool
//
// Command syntax:
//   $ ./genesimmons
// Gene size default=42
//
// Examples:
#include "genetic.h"

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
//this version just assigns fitness as a percentage of maxint, ie should generate all largest numbers
unsigned int calculateFitness(unsigned long chromosome){
    return (unsigned int)(chromosome>>60);
}
#endif

int main( int argc, char *argv[] ) {
    createColony();

    printColony();

    for (unsigned int generation=0; generation<10; generation++){
                
        for(unsigned int i=0; i<4; i++){
            setFitness(i,calculateFitness(getChromosome(i)));
        }
        
        nextGeneration();

        printColony();
    }
} // main
