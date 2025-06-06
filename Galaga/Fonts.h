#pragma once

#include <SFML/Graphics.hpp>

namespace fonts {
    sf::Font font;

    static void setFonts() {
        font.loadFromFile("./Assets/fonts/Swanston.ttf");
    }
}