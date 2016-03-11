#include "species.h"

inline double max( double a, double b) { return ((a<b)?b:a); }
inline double min( double a, double b) { return ((a>b)?b:a); }

Species::Species(unsigned int size, int numLayers, int * layerSizes):size(size){
	for (unsigned int i=0; i<size; i++){
		members.push_back(Network(numLayers, layerSizes));
	}
	currentGeneration=0;
	fitnessRecordsGeneration=0;
}
  
void Species::updateFitnessRecords(){
	totalFitness=0.0;
	lowFitness=members[0].getFitness();
	highFitness=members[0].getFitness();
	for (std::vector<Network>::iterator it=members.begin(); it!=members.end(); ++it){
		totalFitness+=(*it).getFitness();
		lowFitness=min(lowFitness,(*it).getFitness());
		highFitness=max(highFitness,(*it).getFitness());
	}
	avgFitness=totalFitness/size;
	fitnessRecordsGeneration++;
}

//cull to the top half by average, roulette pick 2, combine in both orders to make two kids, and add to members until original size
void Species::newGeneration(){
	std::vector<Network>continuing;
	updateFitnessRecords();
	for (unsigned int i=0; i<size; i++){
		if (members[0].getFitness()>avgFitness){
			continuing.push_back(members[0]);
		}
	}
	members=continuing;
	updateFitnessRecords();

	//do it this way to avoid a copy constructor, note this is still only n^2 which is unavoidable due to the roulette
	while(members.size()<size){
		int pick=RandInt(0,totalFitness);
		for (unsigned int i=0;i<members.size(); i++){
			pick-=members[i].getFitness();
			if(pick<0){
				pick=RandInt(0,totalFitness);
				for (unsigned int j=0; i<members.size(); i++){
					pick-=members[j].getFitness();
					if(pick<0){
						members.push_back(Network(members[i],members[j]));
						if(members.size()<size){
							members.push_back(Network(members[j],members[i]));
						}
						break;
					}
				}
				break;
			}
		}
	}
	currentGeneration++;
}

void Species::runLifecycle(){

}

void Species::update(){
	
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