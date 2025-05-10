#pragma once

#include "grid.hpp"
#include "machinery.hpp"
#include <vector>

// Class representing 
class Factory : public Grid {
private:
    // Data for show pictures of equipment
    std::vector<Machinery> machines;

public:
    Factory(unsigned width, unsigned height, sf::Vector2f pos);
    ~Factory();
    void draw(Window& window);
    void add(Cell::Type type, sf::Vector2i absPos);
    void remove(sf::Vector2i absPos);
};
