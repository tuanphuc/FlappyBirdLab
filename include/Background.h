#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "SFML/Graphics/Sprite.hpp"

class Background : public Entity
{
public:
    Background(TextureHolder &textures);
    void setPosition(sf::Vector2f pos);

private:
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Sprite mSprite;
    sf::Vector2f mPosition;
};

#endif // BACKGROUND_H
