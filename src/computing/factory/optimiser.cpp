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

void Optimiser::solve(Field& field) {
    // Trying to optimise field placement
    
    // Create copy of current field
    Field copy(field);

    // Separating field on areas with width or height is 3 (that is optimal)
    std::vector<Area> areas;
    

    // Analasing areas to place gridded system
    // Checking by size = from most to least



}
