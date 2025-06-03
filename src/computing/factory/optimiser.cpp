#include <vector>
#include <fstream>
#include "optimiser.hpp"


// Optimiser class
Optimiser::Optimiser() {}

void Optimiser::optimise(Field& field) {
    placeWay(field, Process::getLatheCount() + Process::getFurnaceCount() + Process::getWarehouseCount());
    placeObjects(field);
}

void Optimiser::placeWay(Field& field, unsigned count) {
    // Trying to optimise field placement
    // Create copy of current field
    Field copy(field.getWidth(), field.getHeight());

    // Copying voi cells
    for (int y = 0; y < field.getHeight(); ++y) {
        for (int x=0; x < field.getWidth(); ++x) {
            if (field[{x, y}].getType() == CellType::Void) {
                copy[{x, y}].setType(CellType::Void);
            }
        }
    }

    int height = field.getHeight()/3;
    // Check, if last line has only 1 line (no place for way)
    if (field.getHeight()%3 == 2) {
        height++;
    }

    int* positions = new int[height] {0};
    bool* needConnect = new bool[height] {false};
    unsigned index = 0;
    std::vector<sf::Vector2i> notConnectedCells;

    //
    bool hasFree = true;
    while (count > 0 && hasFree) {
        int searchLine = -1;

        // Check, if first line avaliable
        if (positions[0] < field.getWidth()) {
            searchLine = 0;
        }

        for (int i=1; i < height; ++i) {
            // Check, if line full
            if (positions[i] >= field.getWidth()) {
                // Check, if last line
                continue;
            }
            if (positions[i] < positions[i-1]) {
                // Optimisation, to not select lines, if not enough cells to start new line
                if (positions[i-1] > 3*i) {
                    searchLine = i;
                }
            }
            // Need to additional check on obstacles
        }
        // Check, if has line to fill
        if (searchLine == -1) {
            // Connecting all not connected lines
            for (int i=0; i < notConnectedCells.size(); ++i) {
                if (connectCell(copy, copy[{notConnectedCells[i].x, notConnectedCells[i].y}].getIndex(), count)) {
                    // Check, if hasn't connecting ways (error)
                    return;
                }
            }
            field = copy;
            return;
        }

        // Check position on free space
        if (copy[{positions[searchLine], searchLine*3+1}].getType() == CellType::Void) {
            needConnect[searchLine] = true;
            // Checking, how many cells after it inacessible
            for (int i=positions[searchLine]; i < field.getWidth(); ++i) {
                if (copy[{i, searchLine*3+1}].getType() == CellType::Void) {
                    positions[searchLine]++;
                } else {
                    break;
                }
            }
        } else {
            // Adding new column to this space
            // Get index, where adding
            unsigned cellIndex = 0;
            if (searchLine == 0 && positions[0] == 0) {
                // Special variant for first position
                cellIndex = 0;
            } else {
                // Check on connecting to other new system
                if (positions[searchLine] == 0) {
                    // Adding to new line (if not first)
                    index++;
                    cellIndex = index;
                    // Adding to list to connect after
                    notConnectedCells.push_back({positions[searchLine], searchLine*3+1});
                } else if (needConnect[searchLine]) {
                    // Add in same line after obstacle
                    needConnect[searchLine] = false;
                    index++;
                    cellIndex = index;
                    // Adding to list to connect after
                    notConnectedCells.push_back({positions[searchLine], searchLine*3+1});
                } else {
                    // Normal addition to same system
                    // Getting index of previous cell
                    cellIndex = copy[{positions[searchLine]-1, searchLine*3+1}].getIndex();
                }
            }
            // Setting way cell
            copy[{positions[searchLine], searchLine*3+1}].setType(CellType::Way);
            copy[{positions[searchLine], searchLine*3+1}].setIndex(cellIndex);

            // Check on avaliable places
            if (copy[{positions[searchLine], searchLine*3}].getType() != CellType::Void) {
                // Set upper cell
                copy[{positions[searchLine], searchLine*3}].setType(CellType::Unspecified);
                count--;
            }
            if (searchLine*3+2 < field.getHeight() &&
                copy[{positions[searchLine], searchLine*3+2}].getType() != CellType::Void) {
                // Set bottom cell
                copy[{positions[searchLine], searchLine*3+2}].setType(CellType::Unspecified);
                count--;
            }
            // Increasing counter for next line
            positions[searchLine]++;
        }
        // Check, if complete quota
        if (count <= 0) {
            // Linking all not connected piecies
            if (notConnectedCells.size()) {
                if (connectCell(copy, copy[{notConnectedCells[0].x, notConnectedCells[0].y}].getIndex(), count)) {
                    // Check, if hasn't connecting ways (error)
                    return;
                }
                notConnectedCells.erase(notConnectedCells.begin());
            } else {
                // Finishing program
                field = copy;
                return;
            }
        }
    }
    // Finishing program
    field = copy;
}

bool Optimiser::connectCell(Field& copy, unsigned index, unsigned& counter) {
    // Resetting weights
    for (int i=0; i < copy.getHeight(); ++i) {
        for (int j=0; j < copy.getWidth(); ++j) {
            if (copy[{j, i}].getIndex() == index) {
                // Cells, needed to connect in main system
                copy[{j, i}].weight = 1;
            } else {
                // Resetting weights (to infinity)
                copy[{j, i}].weight = -1;
            }
        }
    }

    int step = 1;
    int findCellX = 0, findCellY = 0;
    unsigned findIndex = -1;

    if (findWay(copy, step, findCellX, findCellY, findIndex, index)) {
        return true;
    }

    // Connecting finded cell to main system
    for (int i = step; i > 0; --i) {
        if (trySetWay(copy, findCellX, findCellY+1, i, counter)) {
            findCellY++;
        } else if (trySetWay(copy, findCellX, findCellY-1, i, counter)) {
            findCellY--;
        } else if (trySetWay(copy, findCellX-1, findCellY, i, counter)) {
            findCellX--;
        } else if (trySetWay(copy, findCellX+1, findCellY, i, counter)) {
            findCellX++;
        } else {
            // Error
            return true;
        }
    }

    // Merging current index with finded
    for (int i=0; i < copy.getHeight(); ++i) {
        for (int j=0; j < copy.getWidth(); ++j) {
            if (copy[{j, i}].getIndex() == index) {
                copy[{j, i}].setIndex(findIndex);
            }
        }
    }

    // Upating cells indexes
    return false;
}

bool Optimiser::findWay(Field& copy, int& step, int& findCellX, int& findCellY, unsigned& findIndex, unsigned index) {
    while (true) {
        // Setting near cells to need weight
        for (int i=0; i < copy.getHeight(); ++i) {
            for (int j=0; j < copy.getWidth(); ++j) {
                // Finding current step weights
                if (copy[{j, i}].weight == step) {
                    // Setting all surrounding cells to next weight
                    setCell(copy, j-1, i, step+1);
                    setCell(copy, j, i-1, step+1);
                    setCell(copy, j+1, i, step+1);
                    setCell(copy, j, i+1, step+1);
                }
            }
        }
        // Checking on finding need way
        for (int i=0; i < copy.getHeight(); ++i) {
            for (int j=0; j < copy.getWidth(); ++j) {
                // Check cell on allowable way
                if (copy[{j, i}].weight != (unsigned)(-1) && copy[{j, i}].getType() == CellType::Way && copy[{j, i}].getIndex() != index) {
                    findIndex = copy[{j, i}].getIndex();
                    findCellX = j;
                    findCellY = i;
                    return false;
                }
            }
        }
        step++;
        // Check on overflow
        if (step > 40) {
            return true;
        }
    }
    return true;
}

void Optimiser::setCell(Field& field, int X, int Y, unsigned _weight) {
    if (X >= 0 && Y >= 0 && X < field.getWidth() && Y < field.getHeight()) {
        if (field[{X, Y}].getType() != CellType::Void) {
            if (field[{X, Y}].weight > _weight) {
                field[{X, Y}].weight = _weight;
            }
        }
    }
}

bool Optimiser::trySetWay(Field& field, int X, int Y, unsigned _weight, unsigned& counter) {
    if (X >= 0 && Y >= 0 && X < field.getWidth() && Y < field.getHeight()) {
        if (field[{X, Y}].weight == _weight) {
            // Setting cell as way
            if (field[{X, Y}].getType() == CellType::Unspecified) {
                counter++;
            }
            field[{X, Y}].setType(CellType::Way);
            // Checking, if could add more cells surround cell
            tryPlaceMachine(field, X-1, Y, counter);
            tryPlaceMachine(field, X, Y-1, counter);
            tryPlaceMachine(field, X+1, Y, counter);
            tryPlaceMachine(field, X, Y+1, counter);
            return true;
        }
    }
    return false;
}

void Optimiser::tryPlaceMachine(Field& field, int X, int Y, unsigned& counter) {
    if (X >= 0 && Y >= 0 && X < field.getWidth() && Y < field.getHeight()) {
        if (field[{X, Y}].getType() == CellType::None) {
            field[{X, Y}].setType(CellType::Unspecified);
            counter--;
        }
    }
}

void Optimiser::placeObjects(Field& field) {
    const std::vector<unsigned> counts = Process::getMachinesCount();

    for (int i=0; i < counts.size()/3; ++i) {
        // Replacing unspecified cells with lathes
        placeMachine(field, CellType::Lathe_1, counts[i*3]);
        // Replacing unspecified cells with furnaces
        placeMachine(field, CellType::Furnace_1, counts[i*3+1]);
        // Replacing unspecified cells with furnaces
        placeMachine(field, CellType::Warehouse, counts[i*3+2]);
    }
}

void Optimiser::placeMachine(Field& field, CellType _type, unsigned _count) {
    for (int i=0; i < field.getHeight(); ++i) {
        for (int j=0; j < field.getWidth(); ++j) {
            if (field[{j, i}].getType() == CellType::Unspecified) {
                field[{j, i}].setType(_type);
                // Check, if place enough
                _count--;
                if (_count == 0) {
                    return;
                }
            }
        }
    }
}
