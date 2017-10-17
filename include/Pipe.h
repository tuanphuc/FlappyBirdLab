#ifndef PIPE_H
#define PIPE_H

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "SFML/Graphics/Sprite.hpp"

class Pipe : public Entity
{
public:
    enum Type
    {
        PipeTop,
        PipeBottom,
    };

public:
    Pipe(Type type, const TextureHolder& textures, sf::Vector2f pos);
    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect() const;
    bool getStatus();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    bool isOut;

private:
    sf::Sprite mSprite;
};

#endif // PIPE_H
