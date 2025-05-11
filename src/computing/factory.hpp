#pragma once

#include "grid.hpp"


// Class representing whole workshop
class Factory : public Grid {
public:
    Factory(unsigned width, unsigned height, sf::Vector2f pos);
    ~Factory();
    void draw(Window& window);
    void set(CellType type, sf::Vector2i absPos);
    void remove(sf::Vector2i absPos);
    void reset(sf::Vector2i absPos);
};
