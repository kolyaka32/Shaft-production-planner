#pragma once

#include <fstream>
#include "indexedCell.hpp"


// Matrix n*m with cell
class Field {
private:
    // Array with all cells
    IndexedCell* grid;
    // Dimensions of grid
    unsigned width, height;

public:
    Field(unsigned width, unsigned height);
    ~Field();
    void reset(unsigned width, unsigned height);
    void setWidth(unsigned width);
    void setHeight(unsigned height);
    unsigned getWidth();
    unsigned getHeight();
    // Functions for getting cell at need position
    IndexedCell& getCell(sf::Vector2i pos);
    void save(std::ofstream& fout);
    void load(std::ifstream& fin);
};
