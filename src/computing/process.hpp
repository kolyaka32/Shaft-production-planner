#pragma once

#include <vector>
#include "mechanicalStage.hpp"
#include "thermalStage.hpp"


class Process {
private:
    // Optimal counts of objects
    static int latheCount, furnaceCount, warehouseCount;

protected:
    // Step counts
    static int startStep, stepCount;
    // Function for update process
    static void recalculate(Part target, Part blank);

public:
    Process();

    // Process mechanical steps
    //static std::vector<MechanicalStage> mechanicalStages;
    static MechanicalStage mechanicalStages[4];
    // Process thermal steps
    static ThermalStage thermalStages[4];
    // Semiproducts
    static Part semiproducts[5];
};
