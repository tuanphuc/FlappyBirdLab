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
      mType(type),
      isOut(false)
{
    move(pos);
    setVelocity(-180.f, 0.f);
}

Pipe::Pipe(Type type, const TextureHolder &textures, sf::Vector2f pos, bool dir)
    : Pipe(type, textures, pos)
{
    if(dir)
        setVelocity(-180.f, 100.f);
    else
        setVelocity(-180.f, -100.f);
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

void Pipe::updateCurrent(sf::Time dt)
{
    sf::Vector2f position = getWorldPosition();
    sf::Vector2f velocity = getVelocity();
    if(mType == Type::PipeTop)
    {
        if(position.y + 512 < 50 || position.y + 512 >= (512-50-120))
        {
            velocity.y = -velocity.y;
            setVelocity(velocity);
        }
    }
    if(mType == Type::PipeBottom)
    {
        if(position.y < (50+120) || position.y >= (512-50))
        {
            velocity.y = -velocity.y;
            setVelocity(velocity);
        }
    }
    move(getVelocity() * dt.asSeconds());
}

void Pipe::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
