#include "LearningState.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics/RenderWindow.hpp>

LearningState::LearningState(StateStack& stack, Context context)
    : State(stack, context),
      mPopulation(50),
      mAliveBirds(50),
      mGenerationCounter(0),
      mWorld(*context.window, mCommandQueue, mPopulation),
      mScenePointer(mWorld.getScene()),
      mGeneticLab(mPopulation),
      mPlayer(*context.player),
      mLivingBirds(mPopulation, true),
      mScore(0),
      mFonts(),
      mStatisticsText(),
      mStatisticsUpdateTime()
{
    mStatisticsText.setFont(context.fonts->get(Fonts::Main));
    mStatisticsText.setPosition(5.f, 25.f);
    mStatisticsText.setCharacterSize(15u);
}

void LearningState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    mWorld.draw();
    window.draw(mStatisticsText);
}

bool LearningState::update(sf::Time dt)
{
    mScore += 1;
    mStatisticsUpdateTime += dt;
    if(mStatisticsUpdateTime >= sf::milliseconds(100.f))
    {
        mStatisticsText.setString("Score: " + std::to_string(mScore) + "\n" +
                                  "Max score: " + std::to_string(mGeneticLab.getMaxScore()) + "\n" +
                                  "Generation: " + std::to_string(mGenerationCounter) + "\n" +
                                  "Alive: " + std::to_string(mAliveBirds));
        mStatisticsUpdateTime -= sf::milliseconds(100.f);
    }

    std::vector<unsigned int> dyingBirds = mWorld.update(dt);
    mAliveBirds -= dyingBirds.size();
    if(!dyingBirds.empty())
        for(unsigned int id : dyingBirds)
        {
            mGeneticLab.setScore(id, mScore);
            mLivingBirds.at(id) = false;
        }

    if(!mWorld.hasAlivePlayer())
    {
        mWorld.reset(mPopulation);
        mGeneticLab.update(mScore);
        mScore = 0;
        mGenerationCounter += 1;
        mAliveBirds = mPopulation;
        for(auto b : mLivingBirds)
            b = true;
    }
    else
    {
        CommandQueue& commands = mWorld.getCommandQueue();
        auto positionBirds = mScenePointer[World::BirdLayer]->getWorldPositionChildren();
        auto positionPipes = mScenePointer[World::PipeLayer]->getWorldPositionChildren();

        int index = 0;
        for(unsigned int i=0; i<mLivingBirds.size(); ++i)
        {
            if(mLivingBirds.at(i))
            {
                std::vector<double> inputs;
                inputs.push_back((double)positionBirds.at(index).y / 512);
                for(unsigned int j=0; j<positionPipes.size(); j+=2)
                {
                    if(positionPipes.at(j).x + 50 > positionBirds.at(index).x)
                    {
                        inputs.push_back((double)positionPipes.at(j).y / 512 + 1);
                        break;
                    }
                }
                index += 1;
                if(mGeneticLab.getGeneration().back().at(i).computeNetwork(inputs) > 0.5)
                {
                    mPlayer.controlBird(commands, i);
                }
            }
        }
    }
    return true;
}

bool LearningState::handleEvent(const sf::Event &event)
{
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        mWorld.speedUp();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        mWorld.speedDown();

    return true;
}
