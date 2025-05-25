#include "material.hpp"

Material::Material(float _recrist, float _density)
: recristalisationTemp(_recrist),
density(_density) {}

const Material& Material::operator=(const Material& _mat) {
    recristalisationTemp = _mat.recristalisationTemp;
    return *this;
}

// Standart materials to use
const Material Material::machineSteel{680, 7.8};
const Material Material::alloys{450, 8.8};
const Material Material::heatResistantSteel{850, 7.7};
