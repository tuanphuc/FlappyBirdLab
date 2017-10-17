#include "Pipe.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

Textures::ID toTextureID(Pipe::Type type)
{
    switch(type)
    {
    case Pipe::PipeTop:
        return Textures::PipeTop;
    case Pipe::PipeBottom:
        return Textures::PipeBottom;
    }
    return Textures::PipeTop;
}

Pipe::Pipe(Type type, const TextureHolder &textures, sf::Vector2f pos)
    : Entity(true),
      mSprite(textures.get(toTextureID(type))),
      isOut(false)
{
    move(pos);
    setVelocity(-180.f, 0.f);
}

unsigned int Pipe::getCategory() const
{
    return Category::Pipe;
}

sf::FloatRect Pipe::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Pipe::getStatus()
{
    return isOut;
}

void Pipe::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
