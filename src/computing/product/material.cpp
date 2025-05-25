#include "material.hpp"

Material::Material(float _recrist, float _density)
: recristalisationTemp(_recrist),
density(_density) {}

const Material& Material::operator=(const Material& _mat) {
    recristalisationTemp = _mat.recristalisationTemp;
    density = _mat.density;
    return *this;
}

// Standart materials to use
const Material Material::machineSteel{680, 7800};
const Material Material::alloys{450, 8800};
const Material Material::heatResistantSteel{850, 7700};
