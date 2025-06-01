#pragma once

#include "material.hpp"

class Part {
private:
    void updateMass();
public:
    Part(float diameter=0, float length=0, float rougness=0);
    void set(float diameter, float length, float rougness=0);
    void set(const Part part);
    static void setMaterial(Material material);

    // Properties
    float diameter;
    float length;
    float rougness;
    float mass;
    static Material material;
};
