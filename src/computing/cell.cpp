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

void Cell::loadFrom(char letter) {
    switch (letter) {
    case 'v':
        type = CellType::Void;
        break;

    case 'n':
        type = CellType::None;
        break;

    case 'w':
        type = CellType::Way;
        break;

    case 'c':
        type = CellType::Cargo;
        break;

    case '1':
        type = CellType::Machine_1;
        break;

    case '2':
        type = CellType::Machine_2;
        break;

    case 'f':
        type = CellType::Furnace_1;
        break;
    
    }
}

char Cell::saveAs() {
    switch (type) {
    case CellType::Void:
        return 'v';

    case CellType::None:
        return 'n';

    case CellType::Way:
        return 'w';

    case CellType::Cargo:
        return 'c';

    case CellType::Machine_1:
        return '1';

    case CellType::Machine_2:
        return '2';

    case CellType::Furnace_1:
        return 'f';
    }
    // Default variant with nothing
    return ' ';
}
