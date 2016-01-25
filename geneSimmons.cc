// Purpose: Create gene sample pool
//
// Command syntax:
//   $ ./genesimmons
// Gene size default=42
//
// Examples:

#include <cstdlib>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "genetic.h"

#define NOTRANDOMFITNESS

#define DEFAULTGENESIZE 64 //fits in a long
#define DEFAULTCOLONY 4
#define UINT_MAX 0xFFFFFFFF
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF
#define ULONG_ALMOSTMAX 0x0FFFFFFFFFFFFFFF

using namespace std;

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]<<"ColonySize"<<endl;
    exit( EXIT_FAILURE );
}

#ifdef RANDOMFITNESS
unsigned int calculateFitness( unsigned int totalFitness, unsigned long chromosome){
    return 4;//chosen by random dice roll, guaranteed to be random
}
#else
//this version just assigns fitness as a percentage of maxint, ie should generate all largest numbers
unsigned int calculateFitness( unsigned int totalFitness, unsigned long chromosome){
    return (unsigned int)(chromosome>>60);
}
#endif

int main( int argc, char *argv[] ) {
    srand(time(NULL));

    unsigned int genesize=DEFAULTGENESIZE;
    unsigned int colony_size=DEFAULTCOLONY;
    if (argc>1){
        colony_size=atoi(argv[1]);
    }
    int crossover_rate=900;//times out of a thousand to start crossover at a certain point
                                    //this should be chosen based on genesize
    int mutation_rate=900;//times out of a thousand to mutate bit

    unsigned long chromosomes[colony_size];
    for (unsigned int i=0; i<colony_size; i++){
        chromosomes[i]=((rand() % ULONG_MAX)<<(genesize/2))|(rand() % ULONG_MAX);
    }

    cout<<"Current Generation: ";
    for (unsigned int i=0; i<colony_size; i++){
        cout<<hex<<chromosomes[i]<<" ";
    }
    cout<<endl;

    for (unsigned int generation=0; generation<10; generation++){
                
        /*Determine Fitness*/
        unsigned int fitnessOf[colony_size];
        unsigned int totalFitness=0;//used for selection
        cout<<"Fitness :";
        for(unsigned int i=0; i<colony_size; i++){
            totalFitness+=calculateFitness(totalFitness,chromosomes[i]);
            fitnessOf[i]=totalFitness;//just whatever
            cout<<fitnessOf[i]<<" ";
        }
        cout<<endl;
        /*create new generation*/
        unsigned long newc[colony_size];      
        for (unsigned int i=0; i<colony_size; i++){
            //Make a choice based on fitness for which two chromosomes to combine
            unsigned int a;
            unsigned int b;
            unsigned int fitnesspick=rand() % totalFitness;
            unsigned int j;//position to swap by, chosen by crossover rate

            for(a=0; a<colony_size; a++){
                if(fitnesspick<fitnessOf[a]){
                    break;
                }
            }
            if(a==colony_size){//this shouldn't happen but was. 
                a--;
            }
            fitnesspick=rand()%totalFitness;
            for(b=0; b<colony_size; b++){
                if(fitnesspick<fitnessOf[b]){
                    break;
                }
            }
            if(b==colony_size){
                b--;
            }
            for (j=0; j<genesize; j++){
                if (rand() % 1000 >crossover_rate){
                    break;
                }
            }
            newc[i]=(chromosomes[a]&(ULONG_MAX<<j))|(chromosomes[b]&(ULONG_MAX>>(genesize-j)));
            for(j=0; j<genesize; j++){
                if(rand() % 1000 >mutation_rate){
                    newc[i]=newc[i]^(1<<j);//xor with 1 bitshifted left j times
                }
            }
        }

        /*Update to be current generation and print*/
        cout<<"Current Generation: ";
        for (unsigned int i=0; i<colony_size; i++){
            chromosomes[i]=newc[i];
            cout<<hex<<chromosomes[i]<<" ";
        }
        cout<<endl;

    }
} // main
