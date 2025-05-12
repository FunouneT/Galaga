#include "constants.h"
#include "Level1.h"
#include "Menu.h"

enum class GameState {
    MENU,
    LEVEL1 
};

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Galaga Game");
    sf::Clock clock; 

    // Текущее состояние игры
    GameState currentState = GameState::MENU;

    // Игровые объекты
    Menu mainMenu;
    Level1* currentLevel = nullptr; 

    // Главный игровой цикл
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Передаем события в текущее состояние
            if (currentState == GameState::MENU) {
                mainMenu.handleEvent(event, window);
            }
        }

       
        float frameTime = clock.restart().asMicroseconds() / 300.0f;

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
            currentLevel->update(frameTime);
            currentLevel->draw(window);
        }

 
        window.display();
    }


    delete currentLevel;
    return 0;
}