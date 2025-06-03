#include <vector>
#include "optimiser.hpp"



// Optimiser class
Optimiser::Optimiser() {}

void Optimiser::placeWay(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses) {
    // Trying to optimise field placement
    unsigned count = lathe + furnace + warehouses;

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

    //
    for (int y = 0; y < copy.getHeight(); y += 3) {
        for (int x=0; x < copy.getWidth(); ++x) {
            bool setting = true;
            if (y+1 < copy.getHeight() &&
                copy[{x, y+1}].getType() == CellType::Void) {
                setting = false;
            }
            if (setting) {
                copy[{x, y+1}].setType(CellType::Way);
                // Setting objects
                if (copy[{x, y}].getType() != CellType::Void) {
                    count--;
                }
                if (y+2 < copy.getHeight() &&
                    copy[{x, y+2}].getType() != CellType::Void) {
                    //field[{x, y+2}].setType();
                    count--;
                }
                if (count <= 0) {
                    field = copy;
                    return;
                }
            }
        }
        //
    }

    // Linking all not connected piecies


    //
    field = copy;
}

void Optimiser::optimise(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses) {
    placeWay(field, lathe, furnace, warehouses);
}
