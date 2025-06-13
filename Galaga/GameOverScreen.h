#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

class GameOverScreen {
public:
    GameOverScreen(sf::Font& font);

    void draw(sf::RenderWindow& window, int kills);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window, sf::RenderWindow& gameWindow);

    bool shouldRestart() const;
    void reset();

private:
    void createElements();
    void checkHover(const sf::Vector2f& mousePos);
    void checkClick(const sf::Vector2f& mousePos, sf::RenderWindow& gameWindow);

    sf::Font& font;
    sf::Text gameOverText;
    sf::Text killsText;
    sf::Text restartButton;
    sf::Text exitButton;

    bool restartTriggered;

    sf::RectangleShape overlay;
};