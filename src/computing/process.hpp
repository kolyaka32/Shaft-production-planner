#pragma once

#include <vector>
#include "mechanicalStage.hpp"
#include "thermalStage.hpp"


class Process {
private:
    // Optimal counts of objects
    static int latheCount, furnaceCount, warehouseCount;

protected:
    // Product step part
    // Step counts
    static int startStep, endStep;
    // Process mechanical steps
    //static std::vector<MechanicalStage> mechanicalStages;
    static MechanicalStage mechanicalStages[4];
    // Process thermal steps
    static ThermalStage thermalStages[4];
    // Semiproducts
    static Part semiproducts[5];

    // Process part
    static float partTarget;

    // Function for update process
    static void recalculate(Part target, Part blank);

public:
    Process();

    // Options for get objects count
    static unsigned getLatheCount();
    static unsigned getFurnaceCount();
    static unsigned getWarehouseCount();
};
