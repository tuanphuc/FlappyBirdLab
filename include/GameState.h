#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "World.h"
#include "Player.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class GameState : public State
{
public:
  GameState(StateStack& stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

private:
  World mWorld;
  CommandQueue mCommandQueue;
  Player& mPlayer;
  int mScore;
  FontHolder mFonts;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
};

#endif // GAMESTATE_H
