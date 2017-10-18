#ifndef GENETICLAB_H
#define GENETICLAB_H

#include "Genome.h"
#include <vector>
#include <memory>

class GeneticLab
{
public:
  typedef std::vector<std::vector<Genome>> Generation;

  GeneticLab(unsigned int population);
  GeneticLab(std::vector<unsigned int> architecture, unsigned int population);
  void init();
  void update(unsigned int highestScore);
  Generation& getGeneration();
  void setScore(unsigned int index, unsigned int score);

public:
  // Best networks kepts unchanged for the next generation (rate)
  double mElitism;
  // Population by generation
  unsigned int mPopulation;
  // Number of children breeded in each generation
  unsigned int mNbChildren;
  // New random networks for the next generation (rate)
  double mRandomBehaviour;
  // Crossover factor
  double mCrossoverRate;
  // Mutation rate on the weights of synapses
  double mMutationRate;
  // Interval of the mutation changes on the
  double mMutationRange;
  // Latest generations saved
  unsigned int mHistoric;
  // Only save score (not the network)
  std::vector<int> mScores;

private:
  Generation mGenerations;
  std::vector<unsigned int> mArch;

private:
  std::vector<Genome> breed(Genome g1, Genome g2, unsigned int nbBreedChilds);
  void generateNextGeneration();
};

#endif // GENETICLAB_H
