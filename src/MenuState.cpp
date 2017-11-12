#include "MenuState.h"
#include "Button.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context),
      mGUIContainer()
{
    context.textures->get(Textures::Background).setRepeated(true);
    mBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 1440, 512));
    mBackgroundSprite.setTexture(context.textures->get(Textures::Background));

    // A simple menu demonstration
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(context.window->getView().getSize().x * 0.5f - 60,
                            context.window->getView().getSize().y * 0.2f);
    playButton->setText("Play");
    playButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto learningButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    learningButton->setPosition(playButton->getPosition() + sf::Vector2f(0.f, 60.f));
    learningButton->setText("Learning");
    learningButton->setCallback([this] ()
    {
        requestStackPush(States::Learning);
    });

    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(learningButton->getPosition() + sf::Vector2f(0.f, 60.f));
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(learningButton);
    mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event &event)
{
    mGUIContainer.handleEvent(event);
    return false;
}
