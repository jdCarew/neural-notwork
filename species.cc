#include "species.h"

//I did not write this funciton, I thought it would be part of the vector library, turns out its not but someone already wrote it. I neglected to get source but credit is not mine
double vectorDistance(std::vector<double>::iterator first, std::vector<double>::iterator last, std::vector<double>::iterator first2) {
  double ret = 0.0;
  while (first != last) {
    double dist = (*first++) - (*first2++);
    ret += dist * dist;
  }
  return ret > 0.0 ? sqrt(ret) : 0.0;
}

Species::Species(unsigned int size, int numLayers, int * layerSizes, int compute):size(size),computeGenerations(compute){
	for (unsigned int i=0; i<size; i++){
		members.push_back(Network(numLayers, layerSizes));
	}
	currentGeneration=1;
	fitnessRecordsGeneration=0;
}
  
void Species::updateFitnessRecords(){
	totalFitness=0.0;
	lowFitness=members[0].getFitness();
	highFitness=members[0].getFitness();
	for (unsigned int i=0; i<size; i++){
		totalFitness+=members[i].getFitness();
		lowFitness=min(lowFitness,members[i].getFitness());
		highFitness=max(highFitness,members[i].getFitness());
	}
	avgFitness=totalFitness/size;
	fitnessRecordsGeneration++;
}

//cull to the top half by average, roulette pick 2, combine in both orders to make two kids, and add to members until original size
void Species::newGeneration(){
	updateFitnessRecords();
	for (std::vector<Network>::iterator it=members.begin(); it!=members.end(); ++it){
		if ((*it).getFitness()>avgFitness){
				
			it=members.erase(it);

			--it;//correct for the removed one, might give issues if removing the first element but is recommended online
		}
	}

	updateFitnessRecords();
	//do it this way to avoid a copy constructor, note this is still only n^2 which is unavoidable due to the roulette
	while(members.size()<size){
		int pick=RandFloat(totalFitness);
		for (unsigned int i=0;i<members.size(); i++){
			if(pick<members[i].getFitness()){
				pick=RandFloat(totalFitness);
				for (unsigned int j=0; i<members.size(); i++){
					if(pick<members[j].getFitness()){
						members.push_back(Network(members[i],members[j]));
						if(members.size()<size){
							members.push_back(Network(members[j],members[i]));
						}
						break;
					}
					pick-=members[j].getFitness();
				}
				break;
			}
			pick-=members[i].getFitness();
		}
	}
	currentGeneration++;
}

#ifdef EUCLID
double Species::compare(std::vector<double> expected, std::vector<double> results){
	return vectorDistance(expected.begin(),expected.end(),results.begin());
}
#else
double Species::compare(std::vector<double> expected, std::vector<double> results){
	for (int i=0; i<expected.size(); i++){
		std::cout<<"Expected: "<<expected[i]<<" got: "<<results[i]<<std::endl;
	}
	std::cout<<std::endl;
	return vectorDistance(expected.begin(),expected.end(),results.begin());
}
#endif


void Species::runLifecycle(std::vector<double> input, std::vector<double> expected){
	for (std::vector<Network>::iterator it=members.begin(); it!=members.end(); ++it){
		std::vector<double>results=(*it).evaluate(input);
		(*it).setFitness(compare(expected,results));
	}
}

void Species::update(std::vector<std::vector<double> > testData, std::vector<std::vector<double> > expectedResults){
	assert (testData.size()==expectedResults.size());
	unsigned int numEntries=testData.size();
	unsigned int currentEntry=0;

	for(int i=0; i<computeGenerations; i++){
		for(unsigned int j=0; j<numEntries/computeGenerations; j++){
			runLifecycle(testData[currentEntry],expectedResults[currentEntry]);
			currentEntry++;
		}
		printStats();
		newGeneration();
	}
}

void Species::printStats(){
	if( currentGeneration != fitnessRecordsGeneration){
		updateFitnessRecords();
	}
	std::cout<<"Generation: "<<currentGeneration<<std::endl;
	std::cout<<"Best:    "<<highFitness<<std::endl;
	std::cout<<"Average: "<<avgFitness<<std::endl;
	std::cout<<"Low:     "<<lowFitness<<std::endl;
	/*
	for(unsigned int j=0; j<size;++j){
		members[j].printNetwork();
	}*/
}

double Species::getTotalFitness(){
	if (currentGeneration != fitnessRecordsGeneration){
		updateFitnessRecords();
	}
	return totalFitness;
}

double Species::getHighFitness(){
	if (currentGeneration != fitnessRecordsGeneration){
		updateFitnessRecords();
	}
	return highFitness;
}

double Species::getAvgFitness(){
	if (currentGeneration != fitnessRecordsGeneration){
		updateFitnessRecords();
	}
	return avgFitness;
}

double Species::getLowFitness(){
	if (currentGeneration != fitnessRecordsGeneration){
		updateFitnessRecords();
	}
	return lowFitness;
}

//Network Species::getBest(){
//}