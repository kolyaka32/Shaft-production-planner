#include "cursorMachine.hpp"


CursorMachine::CursorMachine() {
    rect.setSize({cellSize, cellSize});
}

CursorMachine::~CursorMachine() {

}

void CursorMachine::setType(Cell::Type _type) {
    type = _type;
    //rect.setFillColor(getCellColor(type));
}

Cell::Type CursorMachine::getType() {
    return type;
}

void CursorMachine::draw(Window& window, sf::Vector2i _pos) {
    rect.setPosition({float(_pos.x), float(_pos.y)});
    window.draw(rect);
}
