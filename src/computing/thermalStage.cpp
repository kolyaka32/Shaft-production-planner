#include <cmath>
#include "thermalStage.hpp"


ThermalStage::ThermalStage() {}

void ThermalStage::set(Part outPart, float settedPartCapacity) {
    capacity = calculateCapacity(outPart);
    time = calculateTreatmentTime(outPart);
    requiredQuantity = std::ceilf(settedPartCapacity*time/capacity);
}

int ThermalStage::calculateCapacity(Part part) {
    int r = std::ceilf(furnaceDiameter/2/part.diameter);
    return 1+3*r*(r+1);
}

float ThermalStage::calculateTreatmentTime(Part part) {
    return 1 + part.diameter/2/recrystalysationDepth + part.material.recristalisationTemp()/coolingSpeed;
}

int ThermalStage::getCapacity() {
    return capacity;
}

float ThermalStage::getTimePerUnit() {
    return time/capacity/requiredQuantity;
}

float ThermalStage::getTimePerOperation() {
    return time;
}

int ThermalStage::getNeedFurnaces() {
    return requiredQuantity;
}
