#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "Container.h"
#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
public:
  MenuState(StateStack &stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  enum OptionNames {
    Play,
    Learning,
    Exit,
  };

private:
  sf::Sprite mBackgroundSprite;
  GUI::Container mGUIContainer;
};

#endif // MENUSTATE_H
