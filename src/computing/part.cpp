#include "part.hpp"

Material Part::material(Material::MachineSteel);

Part::Part(float _diameter, float _length, float _rougness)
: diameter(_diameter),
length(_length),
rougness(_rougness) {}

void Part::set(float _diameter, float _length, float _rougness) {
    diameter = _diameter;
    length = _length;
    rougness = _rougness;
}

void Part::set(const Part part) {
    diameter = part.diameter;
    length = part.length;
    rougness = part.rougness;
}

void Part::setMaterial(Material _material) {
    material = _material;
}

float Part::getMass() {
    return diameter*diameter*3.141592/4*length/1000000000*material.density();
}
