#pragma once

#include <vector>
#include "mechanicalStage.hpp"
#include "thermalStage.hpp"


class Process {
private:
    // Optimal counts of objects
    static int latheCount, furnaceCount, warehouseCount;
    // Time on production of one part
    static float time;

protected:
    // PInput part
    // Parts for calculations
    static Part targetPart, blankPart;
    // Process part
    static float partTarget;

    // Function for update process
    static void recalculate();

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
    static float getProductionTime();
};
