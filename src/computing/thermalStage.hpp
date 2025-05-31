#pragma once

#include "part.hpp"


class ThermalStage {
private:
    // Furnace constants
    const float furnaceDiameter = 1500;
    const float recrystalysationDepth = 25;
    const float coolingSpeed = 20;

    // Calcualted quantities
    int capacity;  // In parts per one operation
    float time;    // In hours
    // Number of furnaces, needed to complete setted capacity
    int requiredQuantity;

protected:
    int calculateCapacity(Part part);
    float calculateTreatmentTime(Part outPart);

public:
    ThermalStage();
    void set(Part outPart, float settedPartCapacity);
    int getCapacity();
    float getTimePerUnit();
    float getTimePerOperation();
    int getNeedFurnaces();
};
