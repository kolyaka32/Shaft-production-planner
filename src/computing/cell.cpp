#include "cell.hpp"

// Cell class
Cell::Cell(Type _type)
: type(_type) {

}

Cell::Type Cell::getType() {
    return type;
}

void Cell::setType(Cell::Type _type) {
    type = _type;
}
