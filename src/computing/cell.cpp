#include "cell.hpp"


sf::Color getCellColor(Cell::Type type) {
    switch (type) {
    case Cell::Type::None:
        return sf::Color::White;

    case Cell::Type::Way:
        return sf::Color::Yellow;

    case Cell::Type::Machine_1:
        return sf::Color::Red;

    case Cell::Type::Machine_2:
        return sf::Color::Blue;

    case Cell::Type::Furnace_1:
        return sf::Color::Cyan;
    
    default:
        return sf::Color{100};
    }
}

sf::Vector2i getScale(Cell::Type type) {
    switch (type) {
    case Cell::Type::Machine_1:
        return {1, 2};

    case Cell::Type::Machine_2:
        return {2, 3};

    case Cell::Type::Furnace_1:
        return {3, 3};
    
    default:
        return {1, 1};
    }
}

// Cell class
Cell::Cell(Type _type)
: type(_type) {

}

Cell::Type Cell::getType() {
    return type;
}
