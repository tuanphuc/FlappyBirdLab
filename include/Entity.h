#ifndef ENTITY_H
#define ENTITY_H

#include "SceneNode.h"

class Entity : public SceneNode
{
public:
    explicit Entity(bool isAlive);
    void setVelocity(sf::Vector2f v);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity();

    void die();
    virtual bool isDestroyed() const;

private:
    virtual void updateCurrent(sf::Time dt);

private:
    sf::Vector2f mVelocity;
    bool mIsAlive;
};

#endif // ENTITY_H
