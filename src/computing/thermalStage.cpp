#include <cmath>
#include "thermalStage.hpp"


ThermalStage::ThermalStage() {}

void ThermalStage::set(Part outPart, float _settedPartCapacity) {
    setCapacity(calculateCapacity(outPart));
    setOperationTime(calculateTreatmentTime(outPart));
    setRequiredQuantity(_settedPartCapacity);
}

int ThermalStage::calculateCapacity(Part part) {
    int r = std::ceilf(furnaceDiameter/2/part.diameter);
    return 1+3*r*(r+1);
}

float ThermalStage::calculateTreatmentTime(Part part) {
    return 1 + part.diameter/2/recrystalysationDepth + part.material.recristalisationTemp()/coolingSpeed;
}
