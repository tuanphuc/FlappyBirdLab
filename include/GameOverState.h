#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "Container.h"
#include "Player.h"
#include "State.h"
#include "World.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameOverState : public State {
public:
  GameOverState(StateStack &stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  World mWorld;
  CommandQueue mCommandQueue;
  Player &mPlayer;
  sf::Text mGameOverText;
  sf::Text mInstructionText;
};

#endif // GAMEOVERSTATE_H
