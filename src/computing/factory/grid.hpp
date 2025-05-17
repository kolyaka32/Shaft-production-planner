#pragma once

#include "../../app/cycleTemplate.hpp"
#include "indexedCell.hpp"


// Class for draw and calculate objects at the grid
class Grid {
private:
    // Array with all cells
    IndexedCell* grid;
    // Absolute position of first element
    const sf::Vector2f pos;

protected:
    // Dimensions of grid
    unsigned width, height;

    // Functions for getting cell at need position
    IndexedCell& getCell(sf::Vector2i pos);

    // Getting local position (in cells) from absolute coordinate
    sf::Vector2i getLocal(sf::Vector2i absPos);
    // Getting absolute position (in pixels) from local coordinate
    sf::Vector2f getAbs(sf::Vector2i localPos);

public:
    Grid(unsigned width, unsigned height, sf::Vector2f position);
    ~Grid();
    void blit(Window& window);
    bool isSelected(sf::Vector2i pos);
    void setWidth(unsigned width);
    void setHeight(unsigned height);
    void saveGrid(std::string name);
    void loadGrid(std::string name);
};
