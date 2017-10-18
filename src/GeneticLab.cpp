#include "GeneticLab.h"
#include <iostream>
#include <algorithm>
#include <math.h>

GeneticLab::GeneticLab(std::vector<unsigned int> architecture, unsigned int population)
: mElitism(0.2),
  mPopulation(population),
  mNbChildren(1),
  mRandomBehaviour(0.2),
  mCrossoverRate(0.5),
  mMutationRate(0.1),
  mMutationRange(0.5),
  mHistoric(0),
  mScores(),
  mArch(architecture)
{
  // Generate the first generation
  std::vector<Genome> mGenomes;
  for(unsigned int i=0; i<mPopulation; ++i)
  {
    Genome genome(mArch);
    mGenomes.push_back(genome);
  }
  mGenerations.push_back(mGenomes);
}

GeneticLab::GeneticLab(unsigned int population) : GeneticLab({2, 2, 1}, population)
{

}

void GeneticLab::init()
{

}

void GeneticLab::update(unsigned int highestScore)
{
  // Update the highest score of the generation
  mScores.push_back(highestScore);
  // Remove old historic
  while(mGenerations.size() > mHistoric + 1)
  mGenerations.erase(mGenerations.begin());
  // Sort generations according to score
  std::sort(mGenerations.back().begin(), mGenerations.back().end(), Genome::customGreater);
  //    for(auto genome : mGenerations.back())
  //        std::cout << genome.getScore() << " ";
  //    std::cout << std::endl;

  //    std::cout << mGenerations.back().front().getScore() << std::endl;
  generateNextGeneration();

  //    for(auto genome : mGenerations.back())
  //    {
  //        for(auto weight : genome.flattenNetworkWeight())
  //            std::cout << weight << " ";
  //        std::cout << std::endl;
  //    }
  //    std::cout << std::endl;

  //    for(auto weight : mGenerations.back().front().flattenNetworkWeight())
  //        std::cout << weight << " ";
  //    std::cout << std::endl;


}

GeneticLab::Generation& GeneticLab::getGeneration()
{
  return mGenerations;
}

void GeneticLab::setScore(unsigned int index, unsigned int score)
{
  mGenerations.back().at(index).updateScore(score);
}

std::vector<Genome> GeneticLab::breed(Genome g1, Genome g2, unsigned int nbChilds)
{
  std::vector<Genome> childs;
  auto flatten1 = g1.flattenNetworkWeight();
  auto flatten2 = g2.flattenNetworkWeight();
  for(unsigned int i=0; i<nbChilds; ++i)
  {
    Genome child = g1;
    // Crossover
    for(unsigned int i=0; i<flatten2.size(); ++i)
    if ((double)rand()/RAND_MAX <= mCrossoverRate)
    flatten1.at(i) = flatten2.at(i);

    // Mutation
    for(auto& weight: flatten1)
    if ((double)rand()/RAND_MAX <= mMutationRate)
    weight += (double)rand()/RAND_MAX * mMutationRange * 2 - mMutationRange ;

    child.setWeightsFromFlatten(flatten1);
    childs.push_back(child);
  }
  return childs;
}

void GeneticLab::generateNextGeneration()
{
  std::vector<Genome> nextGeneration;
  // Keep an elitism rate of generation
  for(unsigned int i=0; i<(unsigned int)round(mElitism*mPopulation); ++i)
  {
    if(nextGeneration.size() < mPopulation)
    nextGeneration.push_back(mGenerations.back().at(i));
  }
  // Generate an random rate of generation for exploration
  for(unsigned int i=0; i<(unsigned int)round(mRandomBehaviour*mPopulation); ++i)
  {
    if(nextGeneration.size() < mPopulation)
    {
      Genome genome(mArch);
      nextGeneration.push_back(genome);
    }
  }
  // Breed children
  unsigned int max = 0;
  while(true)
  {
    max += 1;
    if(max >= mGenerations.back().size() - 1)
    max = 0;

    for(unsigned int i=0; i<max; ++i)
    {
      auto childs = breed(mGenerations.back().at(i), mGenerations.back().at(max), mNbChildren);
      for(auto child: childs)
      {
        nextGeneration.push_back(child);
        if(nextGeneration.size() >= mPopulation)
        {
          mGenerations.push_back(nextGeneration);
          return;
        }
      }
    }
  }
}
