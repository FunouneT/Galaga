#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    extern sf::Texture playerTexture;
    extern sf::Texture projectileTexture;
    extern sf::Texture enemyTexture;
    extern sf::Texture backgroundLevel1;
    extern sf::Texture backgroundMenu;

    void setTextures();
}