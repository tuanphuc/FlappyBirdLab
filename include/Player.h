#ifndef PLAYER_H
#define PLAYER_H

#include "Command.h"
#include "SFML/Window/Event.hpp"
#include <map>

class CommandQueue;

class Player
{
public:
    enum Action
    {
        Jump,
        JumpId,
    };

    enum MissionStatus
    {
        MissionRunning,
        MissionSuccess,
        MissionFailure
    };

public:
    Player();
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void setMissionStatus(MissionStatus status);
    MissionStatus getMissionStatus() const;
    void controlBird(CommandQueue& commands, unsigned int id);

private:
    void initializeActions();

private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command> mActionBinding;
    MissionStatus mCurrentMissionStatus;
};

#endif // PLAYER_H
