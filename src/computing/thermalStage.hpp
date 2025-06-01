#pragma once

#include "stage.hpp"


class ThermalStage : public Stage {
private:
    // Furnace constants
    const float furnaceDiameter = 1500;
    const float recrystalysationDepth = 25;
    const float coolingSpeed = 20;

protected:
    int calculateCapacity(Part part);
    float calculateTreatmentTime(Part outPart);

public:
    ThermalStage();
    void set(Part outPart, float settedPartCapacity, int batchVolume);
};
