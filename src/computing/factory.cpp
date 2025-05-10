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
