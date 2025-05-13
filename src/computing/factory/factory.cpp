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

bool Factory::checkConnections() {
    unsigned indexCounter = 1;
    bool notConnected = false;

    // Resetting all indexes
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            getCell({x, y}).setIndex(0);
        }
    }

    // Checking grid on way networks
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            if (getCell({x, y}).getType() == CellType::Way
                && getCell({x, y}).getIndex() == 0) {
                // Setting cell and all, connected to it to be same index
                indexConnected({x, y}, indexCounter);
                if (indexCounter != 1) {
                    notConnected = true;
                }
                indexCounter++;
            }
        }
    }

    // Checking on not connected machines
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            if (getCell({x, y}).getIndex() == 0) {
                switch (getCell({x, y}).getType()) {
                case CellType::Machine_1:
                case CellType::Machine_2:
                case CellType::Furnace_1:
                    getCell({x, y}).setIndex(indexCounter);
                    indexCounter++;
                    notConnected = true;
                    break;
                }
            }
        }
    }
    return notConnected;
}

void Factory::indexConnected(sf::Vector2i pos, unsigned _index) {
    // Checking, cell already have index
    if (getCell(pos).getIndex()
        || getCell(pos).getType() == CellType::None
        || getCell(pos).getType() == CellType::Void) {
        return;
    }
    getCell(pos).setIndex(_index);
    // Setting all neighbourth to be same type (recursevly)
    if (getCell(pos).getType() == CellType::Way) {
        if (pos.x > 0) {
            indexConnected({pos.x-1, pos.y}, _index);
        }
        if (pos.x < width) {
            indexConnected({pos.x+1, pos.y}, _index);
        }
        if (pos.y > 0) {
            indexConnected({pos.x, pos.y-1}, _index);
        }
        if (pos.y < height) {
            indexConnected({pos.x, pos.y+1}, _index);
        }
    }
}
