#pragma once

#include <vector>
#include "mechanicalStage.hpp"
#include "thermalStage.hpp"


class Process {
private:
    // Optimal counts of objects
    static int latheCount, furnaceCount, warehouseCount;
    // Time on production of one part
    static float timePerPart;
    // Time to produce whole volume
    static float timePerVolume;

protected:
    // Input part
    // Parts for calculations
    static Part targetPart, blankPart;
    static float partProductionTarget;
    static int partVolumeTarget;

    // Function for update process
    static void recalculate();
    static void calculateVolumeTime();

    // Calculated parameters
    // Step counts
    static int startStep, endStep;
    // Process mechanical steps
    static MechanicalStage mechanicalStages[4];
    // Process thermal steps
    static ThermalStage thermalStages[4];
    // Semiproducts
    static Part semiproducts[5];

public:
    Process();

    // Options for get objects count
    static unsigned getLatheCount();
    static unsigned getFurnaceCount();
    static unsigned getWarehouseCount();
    static float getPartProductionTime();
    static float getVolumeProductionTime();
};
