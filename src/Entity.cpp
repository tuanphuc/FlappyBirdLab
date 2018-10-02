#include "Entity.h"
#include <iostream>

Entity::Entity(bool isAlive) : mVelocity(), mIsAlive(isAlive) {}

void Entity::setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }

void Entity::setVelocity(float vx, float vy) {
  mVelocity.x = vx;
  mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() { return mVelocity; }

void Entity::die() { mIsAlive = false; }

bool Entity::isDestroyed() const { return !mIsAlive; }

void Entity::updateCurrent(sf::Time dt) { move(mVelocity * dt.asSeconds()); }
