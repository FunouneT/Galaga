#include "PauseMenuScreen.h"

PauseMenuScreen::PauseMenuScreen(sf::Font& font) :
    font(font),
    resumeTriggered(false),
    exitTriggered(false)
{
    createElements();
}

void PauseMenuScreen::createElements() {
    overlay.setSize(sf::Vector2f(WINDOWWIDTH, WINDOWHEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    pauseText.setFont(font);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(80);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = pauseText.getLocalBounds();
    pauseText.setOrigin(bounds.width / 2, bounds.height / 2);
    pauseText.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 3);

    resumeButton.setFont(font);
    resumeButton.setString("Resume Game");
    resumeButton.setCharacterSize(50);
    resumeButton.setFillColor(sf::Color::White);

    bounds = resumeButton.getLocalBounds();
    resumeButton.setOrigin(bounds.width / 2, bounds.height / 2);
    resumeButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);

    exitButton.setFont(font);
    exitButton.setString("Exit Game");
    exitButton.setCharacterSize(50);
    exitButton.setFillColor(sf::Color::White);

    bounds = exitButton.getLocalBounds();
    exitButton.setOrigin(bounds.width / 2, bounds.height / 2);
    exitButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 + 80);
}

void PauseMenuScreen::draw(sf::RenderWindow& window) {
    window.draw(overlay);
    window.draw(pauseText);
    window.draw(resumeButton);
    window.draw(exitButton);
}

void PauseMenuScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

        resumeButton.setScale(
            resumeButton.getGlobalBounds().contains(mousePos) ? 1.1f : 1.0f,
            resumeButton.getGlobalBounds().contains(mousePos) ? 1.1f : 1.0f
        );
        resumeButton.setFillColor(
            resumeButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 255, 200) : sf::Color::White
        );

        exitButton.setScale(
            exitButton.getGlobalBounds().contains(mousePos) ? 1.1f : 1.0f,
            exitButton.getGlobalBounds().contains(mousePos) ? 1.1f : 1.0f
        );
        exitButton.setFillColor(
            exitButton.getGlobalBounds().contains(mousePos) ? sf::Color(255, 200, 200) : sf::Color::White
        );
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

        if (resumeButton.getGlobalBounds().contains(mousePos)) {
            resumeTriggered = true;
        }
        else if (exitButton.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
    }
}

bool PauseMenuScreen::shouldResume() const {
    return resumeTriggered;
}

bool PauseMenuScreen::shouldExit() const {
    return exitTriggered;
}

void PauseMenuScreen::reset() {
    resumeTriggered = false;
    exitTriggered = false;
}