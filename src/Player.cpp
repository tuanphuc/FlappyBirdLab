#include "Player.h"
#include "CommandQueue.h"
#include "Bird.h"

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

struct BirdMover
{
    BirdMover()
    {

    }

    void operator () (Bird& bird) const
    {
        bird.flap();
    }

    void operator () (Bird& bird, unsigned int id) const
    {
        if(bird.getId() == id)
            bird.flap();
    }
};

Player::Player()
    : mCurrentMissionStatus(MissionRunning)
{
    initializeActions();
    mKeyBinding[sf::Keyboard::Space] = Jump;
    for(auto& pair : mActionBinding)
        pair.second.category = Category::Bird;
}

void Player::handleEvent(const sf::Event &event, CommandQueue& commands)
{
    if(event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBinding.find(event.key.code);
        if(found != mKeyBinding.end())
            commands.push(mActionBinding[found->second]);
    }
}

void Player::setMissionStatus(MissionStatus status)
{
    mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
    return mCurrentMissionStatus;
}

void Player::controlBird(CommandQueue& commands, unsigned int id)
{
    mActionBinding[JumpId].category = Category::Bird;
    mActionBinding[JumpId].action = derivedAction<Bird>(BirdMover(), id);
    commands.push(mActionBinding[JumpId]);
}

void Player::initializeActions()
{
    mActionBinding[Jump].action = derivedAction<Bird>(BirdMover());
}
