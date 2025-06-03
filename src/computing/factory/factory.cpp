#include "factory.hpp"
#include "optimiser.hpp"


Factory::Factory(Window& window, sf::Vector2f _pos)
: Grid(window, _pos) {
    // First updation of existing grid
    checkConnections();
}

void Factory::draw(Window& window) {
    // Draw back part with grid
    blit(window);
}

void Factory::set(CellType _type, sf::Vector2i absPos) {
    // If selected cell is void - resetting to none
    if (field.getCell(getLocal(absPos)).getType() == CellType::Void) {
        field.getCell(getLocal(absPos)).setType(CellType::None);
    } else {
        // Reset, if set on existing cell
        switch (field.getCell(getLocal(absPos)).getType()) {
        // Update counters
        case CellType::Lathe_1:
        case CellType::Lathe_2:
            latheCount--;
            updateLatheText();
            break;

        case CellType::Furnace_1:
            furnaceCount--;
            updateFurnaceText();
            break;

        case CellType::Warehouse:
            warehouseCount--;
            updateWarehouseText();
            break;
        }
        // Setting selected cell to matched type
        field.getCell(getLocal(absPos)).setType(_type);
        // Increase counters
        switch (_type) {
        case CellType::Lathe_1:
        case CellType::Lathe_2:
            latheCount++;
            updateLatheText();
            break;

        case CellType::Furnace_1:
            furnaceCount++;
            updateFurnaceText();
            break;

        case CellType::Warehouse:
            warehouseCount++;
            updateWarehouseText();
            break;
        }
        // Update linkage of field
        checkConnections();
    }
}

void Factory::remove(sf::Vector2i absPos) {
    switch (field.getCell(getLocal(absPos)).getType()) {
    case CellType::Void:
        // Special action in void cell - can't remove that doesn't exist
        return;

    case CellType::None:
        // Special action in void none - none in building
        field.getCell(getLocal(absPos)).setType(CellType::Void);
        // Update linkage of field
        checkConnections();
        return;

    // Update counters
    case CellType::Lathe_1:
    case CellType::Lathe_2:
        latheCount--;
        updateLatheText();
        break;

    case CellType::Furnace_1:
        furnaceCount--;
        updateFurnaceText();
        break;

    case CellType::Warehouse:
        warehouseCount--;
        updateWarehouseText();
        break;
    }
    // In any normal machine/way - reset to none-type
    field.getCell(getLocal(absPos)).setType(CellType::None);
    // Update linkage of field
    checkConnections();
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
                case CellType::Lathe_1:
                case CellType::Lathe_2:
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
        if (pos.x < field.getWidth()-1) {
            indexConnected({pos.x+1, pos.y}, _index);
        }
        if (pos.y > 0) {
            indexConnected({pos.x, pos.y-1}, _index);
        }
        if (pos.y < field.getHeight()-1) {
            indexConnected({pos.x, pos.y+1}, _index);
        }
    }
}

void Factory::tryOptimize() {
    Optimiser::optimise(field);
    checkConnections();
    recalculateCellsCount();
    updateLatheText();
    updateFurnaceText();
    updateWarehouseText();
}
