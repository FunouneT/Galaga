#include "constants.h"
#include "Level1.h"
#include "Menu.h"
#include "Fonts.h"
#include <iostream>

enum class GameState {
    MENU,
    LEVEL1 
};

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Galaga Game");
    sf::Clock clock; 
    float time;
    fonts::setFonts();

    // Текущее состояние игры
    GameState currentState = GameState::MENU;

    // Игровые объекты
    Menu mainMenu(fonts::font);
    Level1* currentLevel = nullptr; 
    sf::Text fpsIndicator;
    fpsIndicator.setFont(fonts::font);
    fpsIndicator.setCharacterSize(20);
    fpsIndicator.setPosition(sf::Vector2f(WINDOWWIDTH - 50, 0));


    // Главный игровой цикл
    while (window.isOpen()) {
        // Обработка событий

        time = clock.restart().asSeconds();

        while (1 / time > FPS_LIMIT) {
            time = clock.getElapsedTime().asSeconds();
        }
        //std::cout << int(1 / time) << std::endl;
        fpsIndicator.setString(std::to_string(int(1 / time)));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Передаем события в текущее состояние
            if (currentState == GameState::MENU) {
                mainMenu.handleEvent(event, window);
            }
        }

       
        //float frameTime = clock.restart().asMicroseconds() / 300.0f;

        // Проверяем переход между состояниями
        if (currentState == GameState::MENU && mainMenu.shouldStartGame()) {
            currentState = GameState::LEVEL1;
            currentLevel = new Level1();  // Создаем уровень при первом переходе
        }

     
        window.clear();

        // Рендерим текущее состояние
        if (currentState == GameState::MENU) {
            mainMenu.draw(window);
        }
        else if (currentState == GameState::LEVEL1) {
            currentLevel->update(time * 2000);
            currentLevel->draw(window);
        }

        window.draw(fpsIndicator);
 
        window.display();
    }


    delete currentLevel;
    return 0;
}