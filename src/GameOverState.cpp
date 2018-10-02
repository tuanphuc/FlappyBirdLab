#include "GameOverState.h"
#include "Player.h"
#include "ResourceHolder.h"
#include "Utility.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

GameOverState::GameOverState(StateStack &stack, Context context)
    : State(stack, context), mWorld(*context.window, mCommandQueue),
      mPlayer(*context.player), mGameOverText(), mInstructionText() {
  sf::Font &font = context.fonts->get(Fonts::Main);
  sf::Vector2f windowSize(context.window->getSize());

  mGameOverText.setFont(font);
  if (context.player->getMissionStatus() == Player::MissionFailure)
    mGameOverText.setString("Mission failed!");
  else
    mGameOverText.setString("Mission successful!");

  mGameOverText.setCharacterSize(70);
  centerOrigin(mGameOverText);
  mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

  mInstructionText.setFont(font);
  mInstructionText.setString("Presse Backspace to go back to menu");
  centerOrigin(mInstructionText);
  mInstructionText.setPosition(0.5f * windowSize.x, 0.5f * windowSize.y);
}

void GameOverState::draw() {
  sf::RenderWindow &window = *getContext().window;
  window.setView(window.getDefaultView());

  // Create dark, semitransparent background
  sf::RectangleShape backgroundShape;
  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  backgroundShape.setSize(window.getView().getSize());

  window.draw(backgroundShape);
  window.draw(mGameOverText);
  window.draw(mInstructionText);
}

bool GameOverState::update(sf::Time dt) { return false; }

bool GameOverState::handleEvent(const sf::Event &event) {
  CommandQueue &commands = mWorld.getCommandQueue();
  mPlayer.handleEvent(event, commands);

  // Escape pressed, trigger the pause screen
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::BackSpace) {
    requestStateClear();
    requestStackPush(States::Menu);
  }
  return true;
}
