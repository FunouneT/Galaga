#include "Menu.h"
#include "Textures.h"

Menu::Menu(sf::Font& font) :
    font(font),
    startGameTriggered(false),
    showAbout(false)
{
    createBackground();
    createTitle();
    createButtons();
    createAboutWindow(); // Переименовано
}

void Menu::createBackground() {
    backgroundSprite.setTexture(textures::backgroundMenu);
    backgroundSprite.setScale(
        static_cast<float>(WINDOWWIDTH) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(WINDOWHEIGHT) / backgroundSprite.getLocalBounds().height
    );
}

void Menu::createTitle() {
    title.setFont(font);
    title.setString("GALAGA");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2, bounds.height / 2);
    title.setPosition(WINDOWWIDTH / 2, 150);
}

void Menu::createButtons() {
    startButton.setFont(font);
    startButton.setString("Start Game");
    startButton.setCharacterSize(50);
    startButton.setFillColor(sf::Color::White);

    sf::FloatRect bounds = startButton.getLocalBounds();
    startButton.setOrigin(bounds.width / 2, bounds.height / 2);
    startButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 - 50);

    aboutButton.setFont(font);
    aboutButton.setString("About Game");
    aboutButton.setCharacterSize(50);
    aboutButton.setFillColor(sf::Color::White);

    bounds = aboutButton.getLocalBounds();
    aboutButton.setOrigin(bounds.width / 2, bounds.height / 2);
    aboutButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 + 50);
}

void Menu::createAboutWindow() {
    const float windowWidth = 600.f;
    const float windowHeight = 400.f;

    const float windowX = (WINDOWWIDTH - windowWidth) / 2;
    const float windowY = (WINDOWHEIGHT - windowHeight) / 2;

    aboutWindow.setSize(sf::Vector2f(windowWidth, windowHeight));
    aboutWindow.setFillColor(sf::Color(30, 30, 60, 240));
    aboutWindow.setOutlineThickness(2);
    aboutWindow.setOutlineColor(sf::Color::White);
    aboutWindow.setPosition(windowX, windowY);

    
    aboutBackgroundSprite.setScale(
        windowWidth / aboutBackgroundSprite.getLocalBounds().width,
        windowHeight / aboutBackgroundSprite.getLocalBounds().height
    );
    aboutBackgroundSprite.setPosition(windowX, windowY);


    aboutText.setFont(font);
    aboutText.setString(
        "This game was made for the defense\n"
        "of \"Technological (design-technical)\" practice.\n\n"
        "Created by:\n"
        "1. Zviryansky Danil\n"
        "2. Matrekhin Vladislav\n"
        "3. Strelkin Maxim"
    );
    aboutText.setCharacterSize(24);
    aboutText.setFillColor(sf::Color::White);
    aboutText.setLineSpacing(1.5f);

    sf::FloatRect bounds = aboutText.getLocalBounds();
    aboutText.setOrigin(bounds.width / 2, bounds.height / 2);
    aboutText.setPosition(windowX + windowWidth / 2, windowY + windowHeight / 2);
}

void Menu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
        checkHover(mousePos);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        checkClick(mousePos);
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        showAbout = false;
    }
}

void Menu::checkHover(const sf::Vector2f& mousePos) {
    if (!showAbout) {
        if (startButton.getGlobalBounds().contains(mousePos)) {
            startButton.setScale(1.1f, 1.1f);
            startButton.setFillColor(sf::Color(200, 255, 200));
        }
        else {
            startButton.setScale(1.0f, 1.0f);
            startButton.setFillColor(sf::Color::White);
        }

        if (aboutButton.getGlobalBounds().contains(mousePos)) {
            aboutButton.setScale(1.1f, 1.1f);
            aboutButton.setFillColor(sf::Color(200, 200, 255));
        }
        else {
            aboutButton.setScale(1.0f, 1.0f);
            aboutButton.setFillColor(sf::Color::White);
        }
    }
}

void Menu::checkClick(const sf::Vector2f& mousePos) {
    if (!showAbout) {
        if (startButton.getGlobalBounds().contains(mousePos)) {
            startGameTriggered = true;
        }
        else if (aboutButton.getGlobalBounds().contains(mousePos)) {
            showAbout = true;
        }
    }
    else {
        showAbout = false;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    window.draw(title);
    window.draw(startButton);
    window.draw(aboutButton);

    if (showAbout) {

        window.draw(aboutWindow);
        window.draw(aboutText);
    }
}

bool Menu::shouldStartGame() const {
    return startGameTriggered;
}

void Menu::reset() {
    startGameTriggered = false;
    showAbout = false;
}