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

    // ������� ��������� ����
    GameState currentState = GameState::MENU;

    // ������� �������
    Menu mainMenu;
    Level1* currentLevel = nullptr; 

    // ������� ������� ����
    while (window.isOpen()) {
        // ��������� �������
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // �������� ������� � ������� ���������
            if (currentState == GameState::MENU) {
                mainMenu.handleEvent(event, window);
            }
        }

       
        float frameTime = clock.restart().asMicroseconds() / 300.0f;

        // ��������� ������� ����� �����������
        if (currentState == GameState::MENU && mainMenu.shouldStartGame()) {
            currentState = GameState::LEVEL1;
            currentLevel = new Level1();  // ������� ������� ��� ������ ��������
        }

     
        window.clear();

        // �������� ������� ���������
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