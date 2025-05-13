#include "material.hpp"

Material::Material(float recrist)
: recristalisationTemp(recrist) {}


// Standart materials to use
const Material Material::machineSteel{680};
const Material Material::alloys{450};
const Material Material::headResistantSteel{850};
