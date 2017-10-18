#ifndef APPLICATION_H
#define APPLICATION_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Player.h"
#include "StateStack.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class Application
{
public:
  Application();
  void run();

private:
  void processInput();
  void update(sf::Time dt);
  void render();
  void updateStatistics(sf::Time dt);
  void registerStates();

private:
  static const sf::Time TimePerFrame;
  sf::RenderWindow  mWindow;
  TextureHolder mTextures;
  FontHolder mFonts;
  Player mPlayer;
  StateStack mStateStack;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames;
};

#endif // APPLICATION_H
