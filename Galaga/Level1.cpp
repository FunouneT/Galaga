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
    gameOverLineY = WINDOWHEIGHT - 150;

    backgroundSprite.setTexture(textures::backgroundLevel1);
    backgroundSprite.setScale(
        static_cast<float>(WINDOWWIDTH) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(WINDOWHEIGHT) / backgroundSprite.getLocalBounds().height
    );

    currentWave = 1;
    enemiesInWave = 0;
    waveTimer = 0;
    isWaveActive = true;
    enemySpeedMultiplier = 1.0f;
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
    killsText.setString("Kills: 0 | Wave: 1");
}

void Level1::draw(sf::RenderWindow& window)
{
    // Отрисовка фона
    window.draw(backgroundSprite);

    window.draw(player->getSprite());
    for (Entity* proj : projectiles) window.draw(proj->getSprite());
    for (Entity* enem : enemies) window.draw(enem->getSprite());

    window.draw(killsText);

    sf::Vertex line[] = 
    {
        sf::Vertex(sf::Vector2f(0, gameOverLineY), sf::Color::Red),
        sf::Vertex(sf::Vector2f(WINDOWWIDTH, gameOverLineY), sf::Color::Red)
    };
    window.draw(line, 2, sf::Lines);
}

void Level1::update(float time)
{
    if (isGameOver) return;

    // Обновление снарядов
    for (Entity* proj : projectiles) proj->update(time);

    // Реализация управления игроком
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
        if (projectileCD >= PROJCD) 
        {
            Projectile* projectile = new Projectile(textures::projectileTexture, player->getPos());
            projectiles.push_back(projectile);
            projectileCD = 0;
        }
    }

    // Логика волн врагов
    if (isWaveActive) 
    {
        if (enemySpawnCD >= ENEMSPAWNCD && enemiesInWave < 15) 
        {
            Enemy* enemy = new Enemy(textures::enemyTexture, sf::Vector2f(WINDOWWIDTH - 60, 40));
            enemies.push_back(enemy);
            enemy->direction = Direction::Left;
            enemySpawnCD = 0;
            countOfEnemies++;
            enemiesInWave++;
        }

        if (enemiesInWave >= 15 && enemies.empty()) 
        {
            isWaveActive = false;
            waveTimer = 0;
        }
    }
    else 
    {
        waveTimer += time;

        // Реализация спавна волн через время 4,5с
        if (waveTimer >= 15000) 
        {
            currentWave++;
            enemiesInWave = 0;
            isWaveActive = true;
            enemySpeedMultiplier *= 1.1f;

            // Реализация информации о убийствах и волнах
            killsText.setString("Kills: " + std::to_string(enemiesKilled) + " | Wave: " + std::to_string(currentWave));
        }
    }

    // Реализация противников
    for (Entity* enem : enemies)
    {
        if (rand() % 3000 == 1)
            enem->state = State::Sprint;
        if (enem->state == State::Idle) 
        {
            if (enem->getPos().x <= 0) 
            {
                enem->direction = Direction::Right;
                enem->update(sf::Vector2f(0.05, 80 / time), time);
            }
            if (enem->getPos().x > WINDOWWIDTH - 60) 
            {
                enem->direction = Direction::Left;
                enem->update(sf::Vector2f(-0.05, 80 / time), time);
            }

            if (enem->direction == Direction::Left)
                enem->update(sf::Vector2f(-ENEMYSPEED * enemySpeedMultiplier, 0), time);
            if (enem->direction == Direction::Right)
                enem->update(sf::Vector2f(ENEMYSPEED * enemySpeedMultiplier, 0), time);
        }
        else 
        {
            enem->update(sf::Vector2f(0, ENEMYSPEED * 1.5 * enemySpeedMultiplier), time);
        }

        if (enem->getPos().y > gameOverLineY) 
        {
            isGameOver = true;
        }
    }

    // Реализация коллизии снарядов и противников
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
                    killsText.setString("Kills: " + std::to_string(enemiesKilled) + " | Wave: " + std::to_string(currentWave));
                    break;
                }
                else j++;
            }
            if (!enemyIsDead) i++;
        }
    }

    projectileCD += time;
    enemySpawnCD += time;
}