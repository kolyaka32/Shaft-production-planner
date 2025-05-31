#pragma once

#include "part.hpp"


class ThermalStage {
private:
    int capacity;  // In parts per one operation
    float time;    // In hours
    // Furnace constants
    const float furnaceDiameter = 1000;
    const float recrystalysationDepth = 25;
    const float coolingSpeed = 20;

protected:
    int calculateCapacity(Part part);
    float calculateTreatmentTime(Part outPart);

public:
    ThermalStage();
    void set(Part outPart);
    int getCapacity();
    float getTime();
    int getNeedFurnaces(float settedPartCapacity);
};
