#include "Background.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <iostream>

Background::Background(TextureHolder &textures)
    : Entity(true), mSprite(textures.get(Textures::Background)),
      mPosition(0.f, 0.f) {
  textures.get(Textures::Background).setRepeated(true);
  mSprite.setTextureRect(sf::IntRect(0, 0, 1440, 512));
  setVelocity(-18.f, 0.f);
}

void Background::setPosition(sf::Vector2f pos) { mSprite.setPosition(pos); }

void Background::updateCurrent(sf::Time dt) {
  if (getWorldPosition().x <= -288.f)
    move(sf::Vector2f(288.f, 0.f));
  move(getVelocity() * dt.asSeconds());
}

void Background::drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(mSprite, states);
}
