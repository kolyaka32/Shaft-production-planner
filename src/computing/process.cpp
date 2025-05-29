#include "process.hpp"

int Process::startStep = 0, Process::stepCount = 0;
int Process::latheCount = 0, Process::furnaceCount = 0, Process::warehouseCount = 0;
//std::vector<MechanicalStage> Process::mechanicalStages;
//std::vector<ThermalStage> Process::thermalStages;
MechanicalStage Process::mechanicalStages[4];
ThermalStage Process::thermalStages[4];
Part Process::semiproducts[5];

Process::Process() {}

void Process::recalculate(Part target, Part blank) {
    
}
