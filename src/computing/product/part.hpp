#pragma once

#include "material.hpp"

// Class representing single part and it property throw production
class Part {
private:
    Material material;

    // Sizes of part in mm
    float diameter;
    float length;

public:
    Part(Material mat, float diameter, float length);
    float calculateThermalTime();
    float calculateProcessTime();
};
