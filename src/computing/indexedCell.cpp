#include "indexedCell.hpp"


unsigned IndexedCell::globalIndex = 1;


IndexedCell::IndexedCell(CellType type, unsigned _index)
: Cell(type) {
    index = _index;
    if (_index == 0) {
        // Selecting new index, if not connected
        index = globalIndex;
        globalIndex++;
    }
}

void IndexedCell::draw(Window& window, sf::Vector2f absPos) {
    drawer.draw(window, type, absPos);
    // Draw special sign if not connected to main
    if (index != 1) {
        drawer.drawWarning(window, absPos);
    }
}

void IndexedCell::draw(Window& window, sf::Vector2i absPos) {
    drawer.draw(window, type, {(float)absPos.x, (float)absPos.y});
}

unsigned IndexedCell::getIndex() {
    return index;
}

void IndexedCell::setIndex(unsigned _index) {
    index = _index;
}
