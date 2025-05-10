#pragma once

#include "../GUI/GUI.hpp"
#include "cell.hpp"

// Class for draw and calculate objects at the grid
class Grid {
private:
    // Array with all
    Cell* grid;
    

protected:
    // Dimensions of grid
    const unsigned width, height;
    // Absolute position of first element
    const sf::Vector2f pos;

    // Shortcut functions
    Cell& getCell(unsigned X, unsigned Y);
    Cell& getCell(sf::Vector2i pos);

    sf::Vector2i getLocal(sf::Vector2i absPos);
    sf::Vector2f getAbs(sf::Vector2i localPos);

public:
    Grid(unsigned width, unsigned height, sf::Vector2f position);
    ~Grid();
    void blit(Window& window);
    bool isSelected(sf::Vector2i pos);
};
