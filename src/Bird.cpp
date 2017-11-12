#include "Bird.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

#include <iostream>

Bird::Bird(const TextureHolder& textures, sf::Vector2f position, unsigned int id)
    : Entity(true),
      mId(id),
      mGravity(0.f, 1080.f),
      mSprite(textures.get(Textures::Bird))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    this->setPosition(position);
}

Bird::Bird(const TextureHolder &textures, unsigned int id)
    : Bird(textures, sf::Vector2f(200.f, 256.f), id)
{

}

unsigned int Bird::getCategory() const
{
    return Category::Bird;
}

sf::FloatRect Bird::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Bird::addGravity(sf::Time dt)
{
    setVelocity(getVelocity() + mGravity * dt.asSeconds());
}

void Bird::flap()
{
    setVelocity(sf::Vector2f(0.f, -360.f));
}

unsigned int Bird::getId()
{
    return mId;
}

void Bird::updateCurrent(sf::Time dt)
{
    addGravity(dt);
    move(getVelocity() * dt.asSeconds());
}

void Bird::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
