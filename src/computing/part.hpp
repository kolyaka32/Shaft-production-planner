#pragma once

#include "material.hpp"

class Part {
public:
    Part(float diameter=0, float length=0, float rougness=0);
    void set(float diameter, float length, float rougness=0);
    static void setMaterial(Material material);
    float getMass();

    // Properties
    float diameter;
    float length;
    float rougness;
    static Material material;
};
