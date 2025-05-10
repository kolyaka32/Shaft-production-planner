#pragma once

#include "grid.hpp"
#include <vector>

// Class representing 
class Factory : public Grid {
public:
    Factory(unsigned width, unsigned height, sf::Vector2f pos);
    ~Factory();
    void draw(Window& window);
    void set(Cell::Type type, sf::Vector2i absPos);
};
