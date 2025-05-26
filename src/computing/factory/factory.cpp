#include "factory.hpp"


Factory::Factory(sf::Vector2f _pos)
: Grid(_pos) {}

void Factory::draw(Window& window) {
    // Draw back part with grid
    blit(window);
}

void Factory::set(CellType _type, sf::Vector2i absPos) {
    // If selected cell is void - resetting to none
    if (field.getCell(getLocal(absPos)).getType() == CellType::Void) {
        field.getCell(getLocal(absPos)).setType(CellType::None);
    } else {
        // Setting selected cell to matched type
        field.getCell(getLocal(absPos)).setType(_type);
    }
}

void Factory::remove(sf::Vector2i absPos) {
    switch (field.getCell(getLocal(absPos)).getType()) {
    case CellType::Void:
        // Special action in void cell - do nothing
        break;

    case CellType::None:
        // Special action in void none - none in building
        field.getCell(getLocal(absPos)).setType(CellType::Void);
        break;

    default:
        // In any normal machine/way - reset to none-type
        field.getCell(getLocal(absPos)).setType(CellType::None);
        break;
    }
}

void Factory::reset(sf::Vector2i absPos) {
    switch (field.getCell(getLocal(absPos)).getType()) {
    case CellType::Void:
        // Special action in void cell - reset to none type
        field.getCell(getLocal(absPos)).setType(CellType::None);
        break;
    }
}

bool Factory::checkConnections() {
    unsigned indexCounter = 1;
    bool notConnected = false;

    // Resetting all indexes
    for (int y=0; y < field.getHeight(); ++y) {
        for (int x=0; x < field.getWidth(); ++x) {
            field.getCell({x, y}).setIndex(0);
        }
    }

    // Checking grid on way networks
    for (int y=0; y < field.getHeight(); ++y) {
        for (int x=0; x < field.getWidth(); ++x) {
            if (field.getCell({x, y}).getType() == CellType::Way
                && field.getCell({x, y}).getIndex() == 0) {
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
    for (int y=0; y < field.getHeight(); ++y) {
        for (int x=0; x < field.getWidth(); ++x) {
            if (field.getCell({x, y}).getIndex() == 0) {
                switch (field.getCell({x, y}).getType()) {
                case CellType::Machine_1:
                case CellType::Machine_2:
                case CellType::Furnace_1:
                    field.getCell({x, y}).setIndex(indexCounter);
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
    if (field.getCell(pos).getIndex()
        || field.getCell(pos).getType() == CellType::None
        || field.getCell(pos).getType() == CellType::Void) {
        return;
    }
    field.getCell(pos).setIndex(_index);
    // Setting all neighbourth to be same type (recursevly)
    if (field.getCell(pos).getType() == CellType::Way) {
        if (pos.x > 0) {
            indexConnected({pos.x-1, pos.y}, _index);
        }
        if (pos.x < field.getWidth()) {
            indexConnected({pos.x+1, pos.y}, _index);
        }
        if (pos.y > 0) {
            indexConnected({pos.x, pos.y-1}, _index);
        }
        if (pos.y < field.getHeight()) {
            indexConnected({pos.x, pos.y+1}, _index);
        }
    }
}
