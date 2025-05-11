#pragma once

#include "../app/window.hpp"

// Class representing single cell of grid
class Cell {
public:
    // Array representing types of equipment
    enum class Type : unsigned {
        // Type representing unasseseble area
        Void,

        // Type representing empty space
        None,

        // Types for calculations
        Way,

        // Types for storage
        Cargo,

        // Types of machines
        Machine_1,
        Machine_2, 
        Furnace_1,
    };

public:
    Cell(Type type = Type::None);
    Type getType();
    void setType(Type type);
    sf::Color getColor();

protected:
    Type type;
};

// Size of square to draw
const float cellSize = 50.f;
sf::Color getCellColor(Cell::Type type);
