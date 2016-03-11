// the species class defines a species. A species contains a series of neural networks that compete and are assigned fitnesses. 

#ifndef __SPECIES__
#define __SPECIES__

#include "network.h"

#define eventsInLifeCycle 4

class Species{
	std::vector<Network> members;
	unsigned int size;
	double totalFitness;
	double highFitness;
	double lowFitness;
	double avgFitness;
	int fitnessRecordsGeneration;

	int currentGeneration;

	void updateFitnessRecords();

  public:
  	Species(unsigned int size, int numLayers, int * layerSizes);
  	//Although it could be advantageous to have layerSizes vary, that would not work because the genetic algorithm would fail
  	//In fact, keeping to the nameSake, the layerSize as the genetic code it makes more sense for different species to have different layer sizes
  	//That said, it would work to have each species determine it's own layer size, for now accept it as assigned

	//called after we've run enough lifetime simulations to have an accurate enough fitness
  	void newGeneration();

  	//run the network against the provided test data
  	void runLifecycle();

  	//update loop runs the lifecycles on each of the members of a species, the lifecycle will rank their fitness, and then once
  	void update();

  	double getTotalFitness();
  	double getHighFitness();
  	double getAvgFitness();
  	double getLowFitness();
};


#endif