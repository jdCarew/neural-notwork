#include "genetic.h"

unsigned int genesize;
unsigned int colony_size;
int crossover_rate=900;
int mutation_rate=900;
unsigned long *chromosomes;
unsigned int *fitness;

void createColony(){
    genesize=DEFAULTGENESIZE;
    colony_size=DEFAULTCOLONY;
    chromosomes = new unsigned long[colony_size];
    fitness = new unsigned int[colony_size];
    srand(time(NULL));
    for (unsigned int i=0; i<colony_size; i++){
        chromosomes[i]=((rand() % ULONG_MAX)<<(genesize/2))|(rand() % ULONG_MAX);

    }
}

void printColony(){
    std::cout<<"Current Generation: ";
    for (unsigned int i=0; i<colony_size; i++){
        std::cout<<hex<<chromosomes[i]<<" ";
    }
    std::cout<<endl<<dec;
}

void nextGeneration(){
    srand(time(NULL));
    unsigned long newc[colony_size];
    for (unsigned int i=0; i<colony_size; i++){ 
        unsigned int a;//combine colony a with b
        unsigned int b;
        unsigned int fitnesspick=rand() % fitness[colony_size-1];
        unsigned int j;//pos to swap at, chosen by crossover rate

        for(a=0;a<colony_size; a++){
            if(fitnesspick<fitness[a]){
                break;
            }
        }
        if (a==colony_size)a--;

        fitnesspick=rand() % fitness[colony_size-1];
        for(b=0; b<colony_size; b++){
            if(fitnesspick<fitness[b]){
                break;
            }
        }
        if (b==colony_size)b--;
        
        for (j=0; j<genesize; j++){
            if(rand()%1000 > crossover_rate){
                break;
            }
        }
        newc[i]=(chromosomes[a]&(ULONG_MAX<<j))|(chromosomes[b]&(ULONG_MAX>>(genesize-j)));
        for(j=0; j<genesize; j++){
            if(rand() % 1000 > mutation_rate){
                newc[i]=newc[i]^(1<<j);
            }
        }
    }
    for(unsigned int i=0; i<colony_size; i++){
        chromosomes[i]=newc[i];
        fitness[i]=0;
    }
}

unsigned int getChromosome(unsigned int index){
    if(index<colony_size){
        return chromosomes[index];
    }
    return 0;
}

//requires that every fitness up until the current has been correct ordering
void setFitness (unsigned int index, unsigned int value){
    if (index==0){
        fitness[index]=value;
    }else{
        fitness[index]=value+fitness[index-1];
    }
}
