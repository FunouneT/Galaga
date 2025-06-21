#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

class Menu {
public:
    Menu(sf::Font& font);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool shouldStartGame() const;
    void reset();

private:
    void createBackground();
    void createTitle();
    void createButtons();
    void createAboutWindow();
    void checkHover(const sf::Vector2f& mousePos);
    void checkClick(const sf::Vector2f& mousePos);

    sf::Font& font;
    sf::Text title;
    sf::Text startButton;
    sf::Text aboutButton;


    sf::Text aboutText;
    sf::RectangleShape aboutWindow;
    sf::Sprite aboutBackgroundSprite;

    sf::Sprite backgroundSprite;
    bool startGameTriggered;
    bool showAbout;
};