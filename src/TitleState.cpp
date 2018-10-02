#include "TitleState.h"
#include "ResourceHolder.h"
#include "Utility.h"

#include "SFML/Graphics/RenderWindow.hpp"

TitleState::TitleState(StateStack &stack, Context context)
    : State(stack, context), mText() {
  context.textures->get(Textures::Background).setRepeated(true);
  mBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 1440, 512));
  mBackgroundSprite.setTexture(context.textures->get(Textures::Background));

  mText.setFont(context.fonts->get(Fonts::Main));
  mText.setString("Press any key to start");
  centerOrigin(mText);
  mText.setPosition(context.window->getView().getSize().x * 0.5f,
                    context.window->getView().getSize().y * 0.4f);
}

void TitleState::draw() {
  sf::RenderWindow &window = *getContext().window;
  window.draw(mBackgroundSprite);
  window.draw(mText);
}

bool TitleState::update(sf::Time dt) {}

bool TitleState::handleEvent(const sf::Event &event) {
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyReleased) {
    requestStackPop();
    requestStackPush(States::Menu);
  }

  return true;
}
