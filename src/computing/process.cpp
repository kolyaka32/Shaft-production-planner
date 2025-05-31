#include "process.hpp"


// Input part
Part Process::targetPart{60, 200, 4};
Part Process::blankPart{80, 220, 240};
float Process::partProductionTarget = 10;
int Process::partVolumeTarget = 100;
// Process itself
MechanicalStage Process::mechanicalStages[4];
ThermalStage Process::thermalStages[4];
Part Process::semiproducts[5];
// Calculated part (resetted for savety)
int Process::startStep = 0, Process::endStep = 0;
int Process::latheCount = 0, Process::furnaceCount = 0, Process::warehouseCount = 0;
float Process::timePerPart = 0;
float Process::timePerVolume = 0;


Process::Process() {}

void Process::recalculate() {
    // Reset
    latheCount = 0;
    furnaceCount = 0;
    warehouseCount = 0;
    timePerPart = 0;

    // Update step count
    endStep = MechanicalStage::getStepNumber(targetPart.rougness)+1;

    if (blankPart.rougness < targetPart.rougness) {
        startStep = endStep-1;
    } else {
        startStep = MechanicalStage::getStepNumber(blankPart.rougness);
        // Check, if at same step
        if (startStep == endStep-1) {
            startStep = endStep-1;
        }
    }

    // Getting input diamaters from step of production and putting it as out for next stage
    semiproducts[endStep].set(targetPart);
    for (int i=endStep-1; i >= startStep; --i) {
        // Check, if input rougness not from previous step
        if (i == startStep && semiproducts[i+1].rougness < blankPart.rougness) {
            mechanicalStages[i].setFirst(semiproducts[i+1], i, partProductionTarget, blankPart.rougness);
        } else {
            mechanicalStages[i].set(semiproducts[i+1], i, partProductionTarget);
        }
        semiproducts[i].set(mechanicalStages[i].getInputPart());
        thermalStages[i].set(semiproducts[i], partProductionTarget);

        // Updating counters
        latheCount += mechanicalStages[i].getNeedLathes();
        timePerPart += mechanicalStages[i].getTimePerOperation();
        furnaceCount += thermalStages[i].getNeedFurnaces();
        timePerPart += thermalStages[i].getTimePerOperation();
        warehouseCount++;
    }
    calculateVolumeTime();
}

void Process::calculateVolumeTime() {
    // Resetting
    timePerVolume = 0;

    // Counting whole volume time to produce
    float endTime[4];
    for (int i=0; i < 4; ++i) {
        endTime[i] = 0;
    }

    for (int i=startStep; i < endStep; ++i) {
        int stepCapacity = thermalStages[i].getCapacity();
        if (stepCapacity > partVolumeTarget) {
            stepCapacity = partVolumeTarget;
        }
        // Adding start time to all steps, before them can start work
        for (int j=i+1; j < endStep; ++j) {
            endTime[j] += ceilf((float)stepCapacity/mechanicalStages[i].getNeedLathes())*mechanicalStages[i].getTimePerOperation();
            endTime[j] += thermalStages[i].getTimePerOperation();
        }
        float furnaceTime = ceilf((float)ceilf((float)partVolumeTarget/thermalStages[i].getCapacity())/thermalStages[i].getNeedFurnaces())*thermalStages[i].getTimePerOperation();
        float machineTime = ceilf((float)partVolumeTarget/mechanicalStages[i].getNeedLathes())*mechanicalStages[i].getTimePerOperation();

        if (furnaceTime > machineTime) {
            endTime[i] += furnaceTime;
            endTime[i] += ceilf((float)stepCapacity/mechanicalStages[i].getNeedLathes())*mechanicalStages[i].getTimePerOperation();
        } else {
            endTime[i] += machineTime;
            endTime[i] += thermalStages[i].getTimePerOperation();
        }

        // Adding end time to all step before, so them can finish work
        for (int j=i-1; j >= startStep; --j) {
            endTime[j] += ceilf((float)stepCapacity/mechanicalStages[i].getNeedLathes())*mechanicalStages[i].getTimePerOperation();
            endTime[j] += thermalStages[i].getTimePerOperation();
        }
    }
    // Finding maximal time
    for (int i=startStep; i < endStep; ++i) {
        if (endTime[i] > timePerVolume) {
            timePerVolume = endTime[i];
        }
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

float Process::getPartProductionTime() {
    return timePerPart;
}

float Process::getVolumeProductionTime() {
    return timePerVolume;
}
