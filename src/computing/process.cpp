#include "process.hpp"


// Input part
Part Process::targetPart{60, 200, 4};
Part Process::blankPart{80, 220, 240};
float Process::partTarget = 10;
// Process itself
MechanicalStage Process::mechanicalStages[4];
ThermalStage Process::thermalStages[4];
Part Process::semiproducts[5];
// Calculated part (resetted for savety)
int Process::startStep = 0, Process::endStep = 0;
int Process::latheCount = 0, Process::furnaceCount = 0, Process::warehouseCount = 0;
float Process::time = 0;


Process::Process() {}

void Process::recalculate() {
    // Reset
    latheCount = 0;
    furnaceCount = 0;
    warehouseCount = 0;
    time = 0;

    // Update step count
    endStep = MechanicalStage::getStepNumber(targetPart.rougness)+1;

    if (blankPart.rougness < targetPart.rougness) {
        startStep = endStep-1;
    } else {
        startStep = MechanicalStage::getStepNumber(blankPart.rougness);
        // Check, if at same step
        if (startStep+1 == endStep) {
            startStep = endStep-1;
        }
    }

    // Getting input diamaters from step of production and putting it as out for next stage
    semiproducts[endStep].set(targetPart);
    for (int i=endStep-1; i >= startStep; --i) {
        mechanicalStages[i].set(semiproducts[i+1], i);
        semiproducts[i].set(mechanicalStages[i].getInputPart());
        thermalStages[i].set(semiproducts[i]);

        // Updating counters
        latheCount += mechanicalStages[i].getNeedLathes(partTarget);
        time += mechanicalStages[i].getTime();
        furnaceCount += thermalStages[i].getNeedFurnaces(partTarget);
        time += thermalStages[i].getTime();
        warehouseCount++;
    }
}

unsigned Process::getLatheCount() {
    return latheCount;
}

unsigned Process::getFurnaceCount() {
    return furnaceCount;
}

unsigned Process::getWarehouseCount() {
    return warehouseCount;
}

float Process::getProductionTime() {
    return time;
}
