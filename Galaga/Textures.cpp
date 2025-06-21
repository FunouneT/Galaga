#include "Textures.h"

namespace textures {
    sf::Texture playerTexture;
    sf::Texture projectileTexture;
    sf::Texture enemyTexture;
    sf::Texture backgroundLevel1;
    sf::Texture backgroundMenu;
    sf::Texture backgroundAbout;

    void setTextures() {
        playerTexture.loadFromFile("./Assets/textures/player.png");
        projectileTexture.loadFromFile("./Assets/textures/projectile.png");
        enemyTexture.loadFromFile("./Assets/textures/enemy.png");
        backgroundLevel1.loadFromFile("./Assets/textures/level.jpg");
        backgroundMenu.loadFromFile("./Assets/textures/menu.jpg");
    }
}