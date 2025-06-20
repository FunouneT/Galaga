#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(sf::Font& font) :
    font(font),
    restartTriggered(false)
{
    createElements();
}

void GameOverScreen::createElements(){
    overlay.setSize(sf::Vector2f(WINDOWWIDTH, WINDOWHEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
    gameOverText.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 3);

    killsText.setFont(font);
    killsText.setCharacterSize(40);
    killsText.setFillColor(sf::Color::White);
    killsText.setStyle(sf::Text::Bold);
    killsText.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 - 60);

    restartButton.setFont(font);
    restartButton.setString("Restart");
    restartButton.setCharacterSize(50);
    restartButton.setFillColor(sf::Color::White);

    bounds = restartButton.getLocalBounds();
    restartButton.setOrigin(bounds.width / 2, bounds.height / 2);
    restartButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 + 20);

    exitButton.setFont(font);
    exitButton.setString("Exit Game");
    exitButton.setCharacterSize(50);
    exitButton.setFillColor(sf::Color::White);

    bounds = exitButton.getLocalBounds();
    exitButton.setOrigin(bounds.width / 2, bounds.height / 2);
    exitButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 + 100);
}

void GameOverScreen::draw(sf::RenderWindow& window, int kills){
    killsText.setString("Kills: " + std::to_string(kills));
    sf::FloatRect bounds = killsText.getLocalBounds();
    killsText.setOrigin(bounds.width / 2, bounds.height / 2);
    killsText.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 - 60);

    window.draw(overlay);
    window.draw(gameOverText);
    window.draw(killsText);
    window.draw(restartButton);
    window.draw(exitButton);
}

void GameOverScreen::handleEvent(const sf::Event& event, const sf::RenderWindow& window, sf::RenderWindow& gameWindow){
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
        checkHover(mousePos);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        checkClick(mousePos, gameWindow);
    }
}

void GameOverScreen::checkHover(const sf::Vector2f& mousePos){
    bool restartHover = restartButton.getGlobalBounds().contains(mousePos);
    bool exitHover = exitButton.getGlobalBounds().contains(mousePos);

    restartButton.setScale(restartHover ? 1.1f : 1.0f, restartHover ? 1.1f : 1.0f);
    restartButton.setFillColor(restartHover ? sf::Color(200, 255, 200) : sf::Color::White);

    exitButton.setScale(exitHover ? 1.1f : 1.0f, exitHover ? 1.1f : 1.0f);
    exitButton.setFillColor(exitHover ? sf::Color(255, 200, 200) : sf::Color::White);
}

void GameOverScreen::checkClick(const sf::Vector2f& mousePos, sf::RenderWindow& gameWindow)
{
    if (restartButton.getGlobalBounds().contains(mousePos)) {
        restartTriggered = true;
    }
    else if (exitButton.getGlobalBounds().contains(mousePos)) {
        gameWindow.close();
    }
}

bool GameOverScreen::shouldRestart() const{
    return restartTriggered;
}

void GameOverScreen::reset(){
    restartTriggered = false;
}