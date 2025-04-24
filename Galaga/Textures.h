#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    //Задаём переменные для нужных нам текстур
    sf::Texture playerTexture;
    sf::Texture projectileTexture;
    sf::Texture enemyTexture;

    static void setTextures() {
        //Загружаем текстуры из файла
        playerTexture.loadFromFile("./Assets/player.png");
        projectileTexture.loadFromFile("./Assets/projectile.png");
        enemyTexture.loadFromFile("./Assets/enemy.png");
    }
}