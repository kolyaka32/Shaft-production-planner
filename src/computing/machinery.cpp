#include "machinery.hpp"


Machinery::Machinery(Cell::Type _type, sf::Vector2i _coordinats, sf::Vector2f _pos)
: type(_type),
coord(_coordinats) {
    rect.setSize({getSizes().x * cellSize, getSizes().y * cellSize});
    rect.setPosition({_pos.x + coord.x*cellSize, _pos.y+coord.y*cellSize});
    rect.setFillColor(sf::Color::Green);
}

Cell::Type Machinery::getType() {
    return type;
}

sf::Vector2i Machinery::getCoord() {
    return coord;
}

sf::Vector2i Machinery::getSizes() {
    return getScale(type);
}

bool Machinery::at(sf::Vector2i pos) {
    return (pos.x > coord.x) &&
        (pos.y > coord.y) &&
        (pos.x < coord.x + getSizes().x) &&
        (pos.y < coord.y + getSizes().y);
}

void Machinery::draw(Window& window) {
    window.draw(rect);
}

void Machinery::draw(Window& window, sf::Vector2i pos) {
    rect.setPosition({float(pos.x), float(pos.y)});
    window.draw(rect);
}
