#include <cmath>
#include "thermalStage.hpp"


ThermalStage::ThermalStage() {}

void ThermalStage::set(Part outPart, float _settedPartCapacity, int _batchVolume) {
    setCapacity(calculateCapacity(outPart));
    setOperationTime(calculateTreatmentTime(outPart), _batchVolume);
    setRequiredQuantity(_settedPartCapacity, _batchVolume);
    setPowerConsumption(powerInput);
    setCost(ceilf(_batchVolume/getCapacity()), 1.5);
}

int ThermalStage::calculateCapacity(Part part) {
    int r = std::ceilf(furnaceDiameter/2/part.diameter);
    return 1+3*r*(r+1);
}

float ThermalStage::calculateTreatmentTime(Part part) {
    return 1 + part.diameter/2/recrystalysationDepth + part.material.recristalisationTemp()/coolingSpeed;
}

void ThermalStage::saveToFile(std::ofstream& fout) {
    fout << "Thermal stage:\n";
    fout << "Capacity: " << getCapacity() << " parts;\n";
    fout << "Time per load: " << getTimePerOperation() << " hours;\n";
    fout << "Required: " << getReqieredQuantity() << " machines;\n";
    fout << "Cost per batch: " << getBatchCost() << " rub;\n";
    fout << '\n';
}
