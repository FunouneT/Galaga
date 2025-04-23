#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    sf::Texture playerTexture;
    sf::Texture projectileTexture;

    static void setTextures() {
        playerTexture.loadFromFile("./Assets/player.png");
        projectileTexture.loadFromFile("./Assets/projectile.png");
    }
}