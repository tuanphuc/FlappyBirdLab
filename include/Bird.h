#ifndef BIRD_H
#define BIRD_H

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "SFML/Graphics/Sprite.hpp"

class Bird : public Entity {
public:
  Bird(const TextureHolder &textures, sf::Vector2f position, unsigned int id);
  Bird(const TextureHolder &textures, unsigned int id);
  virtual unsigned int getCategory() const;
  virtual sf::FloatRect getBoundingRect() const;
  void addGravity(sf::Time dt);
  void flap();
  unsigned int getId();

private:
  virtual void updateCurrent(sf::Time dt);
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const;

private:
  unsigned int mId;
  sf::Vector2f mGravity;
  sf::Sprite mSprite;
};

#endif // BIRD_H
