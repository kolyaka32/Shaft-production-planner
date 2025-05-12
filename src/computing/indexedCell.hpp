#pragma once

#include "cell.hpp"


// Specified cell, which nown, in to which network it connected
class IndexedCell : public Cell{
private:
    unsigned index;  // 0 index represent none-cennction, other - index of network
    static unsigned globalIndex;  // Global counter of indexes to create new ones

public:
    IndexedCell(CellType type = CellType::None, unsigned index = 0);
    void draw(Window& window, sf::Vector2f absPos);
    void draw(Window& window, sf::Vector2i absPos);
    unsigned getIndex();
    void setIndex(unsigned index);
};
