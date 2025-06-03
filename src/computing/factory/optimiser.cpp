#include <vector>
#include "optimiser.hpp"



// Optimiser class
Optimiser::Optimiser() {}

void Optimiser::optimise(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses) {
    placeWay(field, lathe + furnace + warehouses);
}

void Optimiser::placeWay(Field& field, unsigned _count) {
    // Trying to optimise field placement
    unsigned count = _count;

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
        int searchLine = 0;

        // Check, if first line full
        if (positions[0] == field.getWidth()) {
            searchLine++;
        }

        for (int i=1; i < height; ++i) {
            // Check, if line full
            if (positions[i] == field.getWidth()) {
                // Check, if last line
                if (i == height) {
                    field = copy;
                    return;
                }
                continue;
            }
            if (positions[i-1] > 4*i &&
                positions[i] < positions[i-1]) {
                searchLine = i;
            }
            // Need to additional check on obstacles
        }

        // Check position on free space
        if (copy[{positions[searchLine], searchLine*3+1}].getType() == CellType::Void) {
            positions[searchLine]++;
            needConnect[searchLine] = true;
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
                if (connectCell(copy, notConnectedCells[0], count)) {
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

bool Optimiser::connectCell(Field& copy, sf::Vector2i cell, unsigned& counter) {
    std::vector<sf::Vector2i> posibleCells;


    // Upating cells indexes
    return false;
}
