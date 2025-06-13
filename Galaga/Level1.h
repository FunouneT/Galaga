#pragma once
#include <list>
#include "Player.h"
#include <SFML/Graphics.hpp>

class Level1
{
public:
    Level1();
    ~Level1();

    void update(float);
    void draw(sf::RenderWindow&);

    int projectileCD;
    int enemySpawnCD;
    int countOfEnemies;
    int enemiesKilled;

    Player* player;
    std::list<Entity*> projectiles;
    std::list<Entity*> enemies;

    sf::Text killsText;
    void setupKillsCounter(sf::Font& font);

    bool isGameOver;
    float gameOverLineY;
};