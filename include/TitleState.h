#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class TitleState : public State
{
public:
  TitleState(StateStack& stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  sf::Sprite mBackgroundSprite;
  sf::Text mText;
};

#endif // TITLESTATE_H
