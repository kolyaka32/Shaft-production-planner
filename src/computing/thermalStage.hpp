#pragma once

#include "part.hpp"


class ThermalStage {
private:
    int capacity;
    float time;
    // Furnace constants
    const float furnaceDiameter = 100;
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
