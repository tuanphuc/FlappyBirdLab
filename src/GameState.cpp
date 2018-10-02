#include "GameState.h"
#include "ResourceHolder.h"

#include "SFML/Graphics/RenderWindow.hpp"

GameState::GameState(StateStack &stack, Context context)
    : State(stack, context), mWorld(*context.window, mCommandQueue, 1),
      mPlayer(*context.player), mScore(0), mFonts(), mStatisticsText(),
      mStatisticsUpdateTime() {
  mStatisticsText.setFont(context.fonts->get(Fonts::Main));
  mStatisticsText.setPosition(5.f, 25.f);
  mStatisticsText.setCharacterSize(15u);

  mPlayer.setMissionStatus(Player::MissionRunning);
}

void GameState::draw() {
  sf::RenderWindow &window = *getContext().window;
  mWorld.draw();
  window.draw(mStatisticsText);
}

bool GameState::update(sf::Time dt) {
  mWorld.update(dt);

  mStatisticsUpdateTime += dt;
  if (mStatisticsUpdateTime >= sf::milliseconds(100.f)) {
    mScore += 1;
    mStatisticsText.setString("Score: " + std::to_string(mScore));
    mStatisticsUpdateTime -= sf::milliseconds(100.f);
  }

  if (!mWorld.hasAlivePlayer()) {
    mPlayer.setMissionStatus(Player::MissionFailure);
    requestStackPush(States::GameOver);
  }

  return true;
}

bool GameState::handleEvent(const sf::Event &event) {
  CommandQueue &commands = mWorld.getCommandQueue();
  mPlayer.handleEvent(event, commands);

  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    mWorld.speedUp();
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Down)
    mWorld.speedDown();
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Right)
    mWorld.speedPipeUp();
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Left)
    mWorld.speedPipeDown();

  return true;
}
