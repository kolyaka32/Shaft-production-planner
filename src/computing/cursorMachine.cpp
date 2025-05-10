#include "cursorMachine.hpp"


CursorMachine::CursorMachine() {

}

CursorMachine::~CursorMachine() {

}

void CursorMachine::setType(Cell::Type _type) {
    type = _type;
    rect.setSize({getScale(type).x*cellSize, getScale(type).y*cellSize});
    rect.setFillColor(getCellColor(type));
}

Cell::Type CursorMachine::getType() {
    return type;
}

void CursorMachine::draw(Window& window, sf::Vector2i _pos) {
    rect.setPosition({float(_pos.x), float(_pos.y)});
    window.draw(rect);
}
