#include "factory.hpp"


Factory::Factory(unsigned _W, unsigned _H, sf::Vector2f _pos)
: Grid(_W, _H, _pos) {

}

Factory::~Factory() {

}

void Factory::draw(Window& window) {
    // Draw back part with grid
    blit(window);
}

void Factory::set(CellType _type, sf::Vector2i absPos) {
    // If selected cell is void - resetting to none
    if (getCell(getLocal(absPos)).getType() == CellType::Void) {
        getCell(getLocal(absPos)).setType(CellType::None);
    } else {
        // Setting selected cell to matched type
        getCell(getLocal(absPos)).setType(_type);
    }
}

void Factory::remove(sf::Vector2i absPos) {
    switch (getCell(getLocal(absPos)).getType()) {
    case CellType::Void:
        // Special action in void cell - do nothing
        break;

    case CellType::None:
        // Special action in void none - none in building
        getCell(getLocal(absPos)).setType(CellType::Void);
        break;

    default:
        // In any normal machine/way - reset to none-type
        getCell(getLocal(absPos)).setType(CellType::None);
        break;
    }
}

void Factory::reset(sf::Vector2i absPos) {
    switch (getCell(getLocal(absPos)).getType()) {
    case CellType::Void:
        // Special action in void cell - reset to none type
        getCell(getLocal(absPos)).setType(CellType::None);
        break;
    }
}
