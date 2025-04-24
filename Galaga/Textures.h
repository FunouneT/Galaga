#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    sf::Texture playerTexture;
    sf::Texture projectileTexture;
    sf::Texture enemyTexture;

    static void setTextures() {
        playerTexture.loadFromFile("./Assets/player.png");
        projectileTexture.loadFromFile("./Assets/projectile.png");
        enemyTexture.loadFromFile("./Assets/enemy.png");
    }
}