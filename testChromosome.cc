// Purpose: Create gene sample pool
//
// Command syntax:
//   $ ./genesimmons
// Gene size default=42
//
// Examples:
#include "chromosome.h"

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

void usage(){
    cout<<"GeneSimmons [desiredGenerations] [desiredColonies]"<<endl;
}

int main( int argc, char *argv[] ) {
    //setting parameters
    unsigned int desiredColonies=8;
    unsigned int desiredGenerations=10;
    if (argc>=2){
        desiredGenerations=atoi(argv[1]);
    } 
    if (argc>=3){
        desiredColonies=atoi(argv[2]);
    }
    createColony(64, desiredColonies);

    printColony();

    for (unsigned int generation=0; generation<desiredGenerations; generation++){
                
        for(unsigned int i=0; i<desiredColonies; i++){
            setFitness(i,calculateFitness(getChromosome(i)));
        }
        
        nextGeneration();

//        printColony();
    }
    printColony();
} // main
