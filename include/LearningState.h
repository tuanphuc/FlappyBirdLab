#ifndef LEARNINGSTATE_H
#define LEARNINGSTATE_H

#include "GeneticLab.h"
#include "Player.h"
#include "State.h"
#include "World.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class LearningState : public State {
public:
  LearningState(StateStack &stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  unsigned int mPopulation;
  unsigned int mAliveBirds;
  unsigned int mGenerationCounter;
  World mWorld;
  CommandQueue mCommandQueue;
  std::array<SceneNode *, World::LayerCount> &mScenePointer;
  GeneticLab mGeneticLab;
  Player &mPlayer;
  std::vector<bool> mLivingBirds;
  int mScore;
  FontHolder mFonts;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
};

#endif // LEARNINGSTATE_H
