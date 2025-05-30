#include <cmath>
#include "thermalStage.hpp"


ThermalStage::ThermalStage() {}

void ThermalStage::set(Part outPart) {
    capacity = calculateCapacity(outPart);
    time = calculateTreatmentTime(outPart);
}

int ThermalStage::calculateCapacity(Part part) {
    return std::ceilf(furnaceDiameter/2/part.diameter);
}

float ThermalStage::calculateTreatmentTime(Part part) {
    return 1 + part.diameter/2/recrystalysationDepth + part.material.recristalisationTemp()/coolingSpeed;
}

int ThermalStage::getCapacity() {
    return capacity;
}

float ThermalStage::getTime() {
    return time;
}

int ThermalStage::getNeedFurnaces(float settedPartCapacity) {
    return std::ceilf(settedPartCapacity/capacity*time);
}
