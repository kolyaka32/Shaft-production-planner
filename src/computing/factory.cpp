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

void Factory::set(Cell::Type _type, sf::Vector2i absPos) {
    // Setting selected cell to matched type
    getCell(getLocal(absPos)).setType(_type);
}

void Factory::remove(sf::Vector2i absPos) {
    switch (getCell(getLocal(absPos)).getType()) {
    case Cell::Type::Void:
        // Special action in void cell - do nothing
        break;

    case Cell::Type::None:
        // Special action in void none - none in building
        getCell(getLocal(absPos)).setType(Cell::Type::Void);
        break;

    default:
        // In any normal machine/way - reset to none-type
        getCell(getLocal(absPos)).setType(Cell::Type::None);
        break;
    }
}

void Factory::reset(sf::Vector2i absPos) {
    switch (getCell(getLocal(absPos)).getType()) {
    case Cell::Type::Void:
        // Special action in void cell - reset to none type
        getCell(getLocal(absPos)).setType(Cell::Type::None);
        break;
    }
}
