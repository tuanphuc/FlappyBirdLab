#include "Genome.h"
#include <iostream>
#include <cassert>
#include <math.h>

Genome::Genome(std::vector<unsigned int> architecture)
    : mNeuron{0.0, {}},
      mArch(architecture),
      mScore(0)
{
    populateNetwork(mNetwork, mArch);
}

std::vector<double> Genome::flattenNetworkWeight() const
{
    std::vector<double> flattenWeights;
    for(auto& layer : mNetwork)
    {
        for(auto& neuron : layer)
        {
            if(!neuron.weights.empty())
            {
                for(auto weight : neuron.weights)
                    flattenWeights.push_back(weight);
            }
        }
    }
    return flattenWeights;
}

void Genome::setWeightsFromFlatten(const std::vector<double>& flattenWeight)
{
    unsigned int index = 0;
    for(auto& layer : mNetwork)
    {
        for(auto& neuron : layer)
        {
            if(!neuron.weights.empty())
            {
                for(auto& weight : neuron.weights)
                {
                    weight = flattenWeight.at(index);
                    index += 1;
                }
            }
        }
    }
}

double Genome::computeNetwork(std::vector<double> inputs)
{
    assert(inputs.size() == mNetwork.front().size());

    // Set input layer's values
    for(unsigned int i=0; i<mNetwork.front().size(); ++i)
        mNetwork.front().at(i).value = inputs.at(i);
    // Compute
    for(auto it = mNetwork.begin() + 1; it<mNetwork.end(); ++it)
    {
        for(auto& neuron : *it)
        {
            double sum = 0.0;
            auto prev = it - 1;
            for(unsigned int i=0; i<(*prev).size(); ++i)
            {
                sum += (*prev).at(i).value * neuron.weights.at(i);
            }
            // Activate
            neuron.value = 1.0/(1 + exp(-sum));
        }
    }
//    std::cout << mNetwork.back().back().value << std::endl;
    return mNetwork.back().back().value;
}

void Genome::updateScore(unsigned int score)
{
    mScore = score;
}

unsigned int Genome::getScore()
{
    return mScore;
}

void Genome::populateNeuron(Neuron& neuron, unsigned int nbWeight)
{
    while(nbWeight > 0)
    {
        double weight = ((double)rand() / RAND_MAX) *2 - 1;
        neuron.weights.push_back(weight);
        nbWeight -= 1;
    }
}

void Genome::populateLayer(Layer &layer, unsigned int nbNeuron, unsigned int nbInput)
{
    while(nbNeuron > 0)
    {
        Neuron neuron{0.0, {}};
        populateNeuron(neuron, nbInput);
        layer.push_back(neuron);
        nbNeuron -= 1;
    }
}

void Genome::populateNetwork(Network &network, const std::vector<unsigned int> &mArch)
{
    // Add input layer
    unsigned int input = mArch.front();
    Layer layerInput;
    populateLayer(layerInput, input, 0);
    network.push_back(layerInput);

    // Add hidden layer
    for(unsigned int i=1; i<mArch.size()-1;++i)
    {
        Layer layer;
        populateLayer(layer, mArch.at(i), input);
        network.push_back(layer);
        input = mArch.at(i);
    }

    // Add output layer
    Layer layerOutput;
    populateLayer(layerOutput, mArch.back(), input);
    network.push_back(layerOutput);
}
