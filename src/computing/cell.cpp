#include "cell.hpp"


// Realisation of static object in cell class
CellDrawer Cell::drawer;


Cell::Cell(CellType _type)
: type(_type) {

}

CellType Cell::getType() {
    return type;
}

void Cell::setType(CellType _type) {
    type = _type;
}

void Cell::draw(Window& window, sf::Vector2f absPos) {
    drawer.draw(window, type, absPos);
}

void Cell::draw(Window& window, sf::Vector2i absPos) {
    drawer.draw(window, type, {(float)absPos.x, (float)absPos.y});
}
