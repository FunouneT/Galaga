#include "Level1.h"
#include "Player.h"
#include "constants.h"
#include "Textures.h"
#include "Projectile.h"
#include "Enemy.h"
#include <iostream>

Level1::Level1()
{
    textures::setTextures();
    player = new Player(textures::playerTexture, sf::Vector2f(100, WINDOWHEIGHT - 100));
    projectileCD = 0;
    enemySpawnCD = 0;
    countOfEnemies = 0;
    enemiesKilled = 0;
    isGameOver = false;
    gameOverLineY = WINDOWHEIGHT - 150;  // Линия поражения
}

Level1::~Level1()
{
    delete player;
    for (auto proj : projectiles) delete proj;
    for (auto enem : enemies) delete enem;
}

void Level1::setupKillsCounter(sf::Font& font)
{
    killsText.setFont(font);
    killsText.setCharacterSize(24);
    killsText.setFillColor(sf::Color::White);
    killsText.setPosition(10, 10);
    killsText.setString("Kills: 0");
}

void Level1::draw(sf::RenderWindow& window)
{
    window.draw(player->getSprite());
    for (Entity* proj : projectiles) window.draw(proj->getSprite());
    for (Entity* enem : enemies) window.draw(enem->getSprite());

    window.draw(killsText);

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(0, gameOverLineY), sf::Color::Red),
        sf::Vertex(sf::Vector2f(WINDOWWIDTH, gameOverLineY), sf::Color::Red)
    };
    window.draw(line, 2, sf::Lines);
}

void Level1::update(float time)
{
    if (isGameOver) return;  // Если игра окончена, не обновляем состояние

    // Обновление снарядов
    for (Entity* proj : projectiles) proj->update(time);

    // Управление игроком
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        player->state = State::Sprint;
    else
        player->state = State::Idle;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (player->getPos().x >= 0))
        player->update((player->state == State::Sprint ? -PLAYERSPEED * 1.5 : -PLAYERSPEED), time);
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (player->getPos().x <= WINDOWWIDTH - 70))
        player->update((player->state == State::Sprint ? PLAYERSPEED * 1.5 : PLAYERSPEED), time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (projectileCD >= PROJCD) {
            Projectile* projectile = new Projectile(textures::projectileTexture, player->getPos());
            projectiles.push_back(projectile);
            projectileCD = 0;
        }
    }

    // Создание противников
    if (enemySpawnCD >= ENEMSPAWNCD && countOfEnemies < 20) {
        Enemy* enemy = new Enemy(textures::enemyTexture, sf::Vector2f(WINDOWWIDTH - 60, 40));
        enemies.push_back(enemy);
        enemy->direction = Direction::Left;
        enemySpawnCD = 0;
        countOfEnemies++;
    }

    // Обновление противников
    for (Entity* enem : enemies)
    {
        if (rand() % 3000 == 1)
            enem->state = State::Sprint;
        if (enem->state == State::Idle) {
            if (enem->getPos().x <= 0) {
                enem->direction = Direction::Right;
                enem->update(sf::Vector2f(0.05, 80 / time), time);
            }
            if (enem->getPos().x > WINDOWWIDTH - 60) {
                enem->direction = Direction::Left;
                enem->update(sf::Vector2f(-0.05, 80 / time), time);
            }

            if (enem->direction == Direction::Left)
                enem->update(sf::Vector2f(-ENEMYSPEED, 0), time);
            if (enem->direction == Direction::Right)
                enem->update(sf::Vector2f(ENEMYSPEED, 0), time);
        }
        else {
            enem->update(sf::Vector2f(0, ENEMYSPEED * 1.5), time);

            // Проверка перехода линии
            if (enem->getPos().y > gameOverLineY) {
                isGameOver = true;
            }
        }
    }

    // Коллизия снарядов и противников
    if (!projectiles.empty() && !enemies.empty()) {
        for (auto i = enemies.begin(); i != enemies.end();)
        {
            bool enemyIsDead = false;
            Entity* enem = *i;
            for (auto j = projectiles.begin(); j != projectiles.end();)
            {
                Entity* proj = *j;
                if (enem->collide(*proj)) {
                    i = enemies.erase(i);
                    j = projectiles.erase(j);
                    delete enem;
                    delete proj;
                    enemyIsDead = true;
                    enemiesKilled++;
                    killsText.setString("Kills: " + std::to_string(enemiesKilled));
                    break;
                }
                else j++;
            }
            if (!enemyIsDead) i++;
        }
    }

    // Обновление кулдаунов
    projectileCD += time;
    enemySpawnCD += time;
}