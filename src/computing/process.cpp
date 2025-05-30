#include "process.hpp"

int Process::startStep = 0, Process::endStep = 0;
int Process::latheCount = 0, Process::furnaceCount = 0, Process::warehouseCount = 0;
float Process::partTarget = 100;
MechanicalStage Process::mechanicalStages[4];
ThermalStage Process::thermalStages[4];
Part Process::semiproducts[5];

Process::Process() {}

void Process::recalculate(Part target, Part blank) {
    // Resettings
    latheCount = 0;
    furnaceCount = 0;
    warehouseCount = 0;

    // Update step count
    endStep = MechanicalStage::getStepNumber(target.rougness)+1;

    if (blank.rougness < target.rougness) {
        startStep = endStep-1;
    } else {
        startStep = MechanicalStage::getStepNumber(blank.rougness);
        // Check, if at same step
        if (startStep+1 == endStep) {
            startStep = endStep-1;
        }
    }

    // Getting input diamaters from step of production and putting it as out for next stage
    semiproducts[endStep].set(target);
    for (int i=endStep-1; i >= startStep; --i) {
        mechanicalStages[i].set(semiproducts[i+1], i);
        thermalStages[i].set(semiproducts[i]);
        semiproducts[i].set(mechanicalStages[i].getInputPart());

        // Updating counters
        latheCount += mechanicalStages[i].getNeedLathes(partTarget);
        furnaceCount += thermalStages[i].getNeedFurnaces(partTarget);
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
