#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    sf::Texture playerTexture;
    sf::Texture projectileTexture;
    sf::Texture enemyTexture;

    static void setTextures() {
        playerTexture.loadFromFile("./Assets/textures/player.png");
        projectileTexture.loadFromFile("./Assets/textures/projectile.png");
        enemyTexture.loadFromFile("./Assets/textures/enemy.png");
    }
}