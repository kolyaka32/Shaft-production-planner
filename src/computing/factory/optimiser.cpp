#include <vector>
#include "optimiser.hpp"


// Area class
Area::Area() {}

Area::Area(int _X, int _Y, int _width, int _height) {
    width = _width;
    height = _height;
    X = _X;
    Y = _Y;
}


// Optimiser class
Optimiser::Optimiser() {}

void Optimiser::placeWay(Field& field, unsigned count) {
    // Trying to optimise field placement
    
    // Create copy of current field
    Field copy(field);

    // Analasing areas to place gridded system
    // Checking by size = from most to least
    int counts[8]{0};

    //
    for (int startY=0; startY < 4; ++startY) {
        // Checking all horizontal rects with height=3
        
        // Check line under way
        for (int y = startY+1; y < field.getHeight(); y += 3) {
            // Check, if column avalible
            if (field[])
        }

        // Check line above way (if can)
        if (startY == 0) {
            continue;
        }

    }
}

void Optimiser::placeObjects(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses) {
    
}
