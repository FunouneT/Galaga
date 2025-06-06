#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    //Задаём переменные для нужных нам текстур
    sf::Texture playerTexture;
    sf::Texture projectileTexture;
    sf::Texture enemyTexture;

    static void setTextures() {
        //Загружаем текстуры из файла
        playerTexture.loadFromFile("./Assets/textures/player.png");
        projectileTexture.loadFromFile("./Assets/textures/projectile.png");
        enemyTexture.loadFromFile("./Assets/textures/enemy.png");
    }
}