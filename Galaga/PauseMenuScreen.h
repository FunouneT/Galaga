#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

class PauseMenuScreen {
public:
    PauseMenuScreen(sf::Font& font);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    bool shouldResume() const;
    bool shouldExit() const;
    void reset();

private:
    void createElements();

    sf::Font& font;
    sf::RectangleShape overlay;
    sf::Text pauseText;
    sf::Text resumeButton;
    sf::Text exitButton;

    bool resumeTriggered;
    bool exitTriggered;
};