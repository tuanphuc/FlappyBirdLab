#ifndef GENOME_H
#define GENOME_H

#include<vector>

class Genome
{
public:
  Genome(std::vector<unsigned int> architecture);

public:
  struct Neuron
  {
    double value;
    std::vector<double> weights;
  };
  Neuron mNeuron;

  // sort using a custom function object
  static struct {
    bool operator()(Genome a, Genome b) const
    {
      return a.mScore > b.mScore;
    }
  } customGreater;

  typedef std::vector<Neuron> Layer;
  typedef std::vector<Layer> Network;

  std::vector<double> flattenNetworkWeight() const;
  void setWeightsFromFlatten(const std::vector<double>& flattenWeight);
  double computeNetwork(std::vector<double> inputs);
  void updateScore(unsigned int score);
  unsigned int getScore();

private:
  std::vector<unsigned int> mArch;
  unsigned int mScore;
  Network mNetwork;
  void populateNeuron(Neuron& neuron, unsigned int nbWeight);
  void populateLayer(Layer& layer, unsigned int nbNeuron, unsigned int nbInput);
  void populateNetwork(Network& network, const std::vector<unsigned int>& mArch);

};

#endif // GENOME_H
