#ifndef __GENETIC__
#define __GENETIC__

#include <cstdlib>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define DEFAULTGENESIZE 64 //fits in a long
#define DEFAULTCOLONY 4
#define UINT_MAX 0xFFFFFFFF
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF
#define ULONG_ALMOSTMAX 0x0FFFFFFFFFFFFFFF

void createColony (unsigned int genesize=DEFAULTGENESIZE, unsigned int colonysize=DEFAULTCOLONY);

void nextGeneration();

void printColony();

unsigned long getChromosome(unsigned int index);

void setFitness (unsigned int index, unsigned int value);

#endif
