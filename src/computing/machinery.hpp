#pragma once

#include "cell.hpp"

// Class representing
class Machinery {
public:
    // Basic functions work with
    Machinery(Cell::Type type, sf::Vector2i coordinats, sf::Vector2f startPos = {0, 0});
    Cell::Type getType();
    sf::Vector2i getSizes();
    sf::Vector2i getCoord();
    bool at(sf::Vector2i coord);
    void draw(Window& window);
    void draw(Window& window, sf::Vector2i pos);

protected:
    Cell::Type type;
    sf::Vector2i coord;
    sf::RectangleShape rect;
};
