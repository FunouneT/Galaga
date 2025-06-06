#include "Menu.h"
#include <iostream>

Menu::Menu(sf::Font font) : startGameTriggered(false) {
    //if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
    //    std::cerr << "Error loading font. Using default SFML font.\n";
        // � ������ ������ SFML ����� ������������ ���������� �����
    //}
    this->font = font;
    createBackground();
    createTitle();
    createButtons();
}

// �������� ������������ ����
void Menu::createBackground() {

    background.setPrimitiveType(sf::Quads);
    background.resize(4);


    background[0].position = { 0, 0 };                   
    background[1].position = { WINDOWWIDTH, 0 };        
    background[2].position = { WINDOWWIDTH, WINDOWHEIGHT }; 
    background[3].position = { 0, WINDOWHEIGHT };      

    // ����������� ����� ��� ��������� (����� -> ����������)
    background[0].color = sf::Color(0, 0, 139);    // �����-�����
    background[1].color = sf::Color(0, 0, 139);
    background[2].color = sf::Color(128, 0, 128);  // ����������
    background[3].color = sf::Color(128, 0, 128);
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

// �������� ������ ����
void Menu::createButtons() {
    startButton.setFont(font);
    startButton.setString("Start Game");
    startButton.setCharacterSize(40);
    startButton.setFillColor(sf::Color::White);

    sf::FloatRect bounds = startButton.getLocalBounds();
    startButton.setOrigin(bounds.width / 2, bounds.height / 2);
    startButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);

    // ������ "About Game"
    aboutButton.setFont(font);
    aboutButton.setString("About Game");
    aboutButton.setCharacterSize(40);
    aboutButton.setFillColor(sf::Color::White);


    bounds = aboutButton.getLocalBounds();
    aboutButton.setOrigin(bounds.width / 2, bounds.height / 2);
    aboutButton.setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT / 2 + 80);
}

// ��������� ������� ����
void Menu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseMoved) {
        // ����������� ���������� ����
        sf::Vector2f mousePos = window.mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });
        checkHover(mousePos);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y });
        checkClick(mousePos);
    }
}

// �������� ��������� �� ������
void Menu::checkHover(const sf::Vector2f& mousePos) {
    bool startHover = startButton.getGlobalBounds().contains(mousePos);
    bool aboutHover = aboutButton.getGlobalBounds().contains(mousePos);

    // ������ ��� ���������: ���������� � ���������
    startButton.setScale(startHover ? 1.1f : 1.0f, // ��������� � f, ����� �++ ����� ����� float
        startHover ? 1.1f : 1.0f);
    startButton.setFillColor(startHover ? sf::Color(200, 200, 255) : sf::Color::White);

    aboutButton.setScale(aboutHover ? 1.1f : 1.0f,
        aboutHover ? 1.1f : 1.0f);
    aboutButton.setFillColor(aboutHover ? sf::Color(200, 200, 255) : sf::Color::White);
}

// ��������� ������ �� �������
void Menu::checkClick(const sf::Vector2f& mousePos) {
    if (startButton.getGlobalBounds().contains(mousePos)) {
        startGameTriggered = true;  // ������������� ���� ������ ����
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background); 
    window.draw(title);       
    window.draw(startButton); 
    window.draw(aboutButton);
}

// �������� ������������� ������ ����
bool Menu::shouldStartGame() const {
    return startGameTriggered;
}

// ����� ��������� ����
void Menu::reset() {
    startGameTriggered = false;
}