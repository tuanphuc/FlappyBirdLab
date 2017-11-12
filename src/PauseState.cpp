#include "PauseState.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context),
      mBackgroundSprite(),
      mPauseText(),
      mInstructionText()
{
    sf::Vector2f viewSize = context.window->getView().getSize();

    mPauseText.setFont(context.fonts->get(Fonts::Main));
    mPauseText.setString("Game Paused");
    mPauseText.setCharacterSize(50);
    centerOrigin(mPauseText);
    mPauseText.setPosition(0.5f * viewSize.x, 0.3f * viewSize.y);

    mInstructionText.setFont(context.fonts->get(Fonts::Main));
    mInstructionText.setString("Presse:\n"
                               "\tEscape: return to game\n"
                               "\tUp: speed game up\n"
                               "\tDown: speed game down\n"
                               "\tBackspace: Return to main menu");
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 200));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mPauseText);
    window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event &event)
{
    if(event.type != sf::Event::KeyPressed)
        return false;

    if(event.key.code == sf::Keyboard::Escape)
    {
        // Escape pressed, remove itself to return to the game
        requestStackPop();
    }

    if(event.key.code == sf::Keyboard::BackSpace)
    {
        // Backspace pressed, clear state and return to Menu
        requestStateClear();
        requestStackPush(States::Menu);
    }

    return false;
}
