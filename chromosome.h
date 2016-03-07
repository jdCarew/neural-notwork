#ifndef __GENETIC__
#define __GENETIC__

#include <vector>
#include <math.h>
#include <cstdlib>
#include <iostream>



struct weightsGenome{
  std::vector<double> weights;
  double fitness;

  weightsGenome():fitness(0){}

  weightsGenome( std::vector <double> w, double f): weights(w), fitness(f){}

  //overload '<' used for sorting
  friend bool operator<(const weightsGenome& lhs, const weightsGenome& rhs)
  	{	return (lhs.fitness < rhs.fitness); }
};

class CGenAlg{

  //each element is the genome for an entire network
  std::vector <weightsGenome> population;

  int populationSize;	//aka how many networks
  int weightsPerGenome;
  double totalFitness;
  double bestFitness;
  double averageFitness;
  double worstFitness;
  int indexFittestGenome;

  //probability that a chromosomes bits will mutate.
  //Try figures around 0.05 to 0.3
  double m_dMutationRate;

  //probability of chromosomes crossing over bits
  //0.7 is pretty good
  double m_dCrossoverRate;

  int generationCounter;

  void Crossover(const vector<double> &mum, const vector<double> &dad, vector<double> &baby1, vector<double> &baby2); 

  void Mutate(vector<double> &chromo); 

  SGenome GetChromoRoulette(); 

  void GrabNBest(int NBest, const int NumCopies, vector<SGenome> &vecPop);

  void CalculateBestWorstAvTot(); 

  void Reset();

  public:

  CGenAlg(int popsize, double MutRat, double CrossRat, int numweights);

  //this runs the GA for one generation.
  vector<SGenome> Epoch(vector<SGenome> &old_pop);

  //-------------------accessor methods

  vector<SGenome> GetChromos()const{return m_vecPop;}

  double AverageFitness()const{return m_dTotalFitness / m_iPopSize;}

  double BestFitness()const{return m_dBestFitness;}

};

#endif
