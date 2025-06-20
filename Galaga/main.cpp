#include "constants.h"
#include "Level1.h"
#include "Menu.h"
#include "Fonts.h"
#include "GameOverScreen.h"
#include "PauseMenuScreen.h"
#include "Textures.h" // Добавлен новый заголовок
#include <iostream>

enum class GameState 
{
    MENU,
    LEVEL1,
    GAME_OVER,
    PAUSED
};

int main() 
{
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Galaga Game");
    sf::Clock clock;
    float time;
    fonts::setFonts();
    textures::setTextures();

    GameState currentState = GameState::MENU;
    Menu mainMenu(fonts::font);
    Level1* currentLevel = nullptr;
    GameOverScreen gameOverScreen(fonts::font);
    PauseMenuScreen pauseMenuScreen(fonts::font);

    sf::Text fpsIndicator;
    fpsIndicator.setFont(fonts::font);
    fpsIndicator.setCharacterSize(20);
    fpsIndicator.setPosition(sf::Vector2f(WINDOWWIDTH - 50, 0));

    while (window.isOpen()) 
    {
        time = clock.restart().asSeconds();

        while (1 / time > FPS_LIMIT) 
        {
            time = clock.getElapsedTime().asSeconds();
        }

        fpsIndicator.setString(std::to_string(int(1 / time)));

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (currentState) 
            {
            case GameState::MENU:
                mainMenu.handleEvent(event, window);
                break;
            case GameState::GAME_OVER:
                gameOverScreen.handleEvent(event, window, window);
                break;
            case GameState::LEVEL1:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
                {
                    currentState = GameState::PAUSED;
                }
                break;
            case GameState::PAUSED:
                pauseMenuScreen.handleEvent(event, window);
                if (pauseMenuScreen.shouldResume()) 
                {
                    currentState = GameState::LEVEL1;
                    pauseMenuScreen.reset();
                }
                break;
            }
        }

        if (currentState == GameState::MENU && mainMenu.shouldStartGame()) 
        {
            currentState = GameState::LEVEL1;
            currentLevel = new Level1();
            currentLevel->setupKillsCounter(fonts::font);
        }

        if (currentState == GameState::LEVEL1 && currentLevel->isGameOver) 
        {
            currentState = GameState::GAME_OVER;
        }

        if (currentState == GameState::GAME_OVER) 
        {
            if (gameOverScreen.shouldRestart()) 
            {
                delete currentLevel;
                currentLevel = new Level1();
                currentLevel->setupKillsCounter(fonts::font);
                currentState = GameState::LEVEL1;
                gameOverScreen.reset();
            }
        }

        window.clear();

        switch (currentState) 
        {
        case GameState::MENU:
            mainMenu.draw(window);
            break;
        case GameState::LEVEL1:
            currentLevel->update(time * 2000);
            currentLevel->draw(window);
            break;
        case GameState::GAME_OVER:
            currentLevel->draw(window);
            gameOverScreen.draw(window, currentLevel->enemiesKilled);
            break;
        case GameState::PAUSED:
            currentLevel->draw(window);
            pauseMenuScreen.draw(window);
            break;
        }

        window.draw(fpsIndicator);
        window.display();
    }

    delete currentLevel;
    return 0;
}