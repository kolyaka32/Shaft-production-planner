#include <cmath>
#include "mechanicalStage.hpp"


MechanicalStage::MechanicalStage() {}

void MechanicalStage::setNew(Part outPart, float _stepNumber) {
    stepNumber = _stepNumber;
    inputPart = calculateInputDiameter(stepNumber, outPart.diameter), calculateInputLength(stepNumber, outPart.length);
    time = calculateTime();
    powerConsumption = calculatePowerConsumption();
}

int MechanicalStage::getStepNumber(float rougness) {
    if (rougness < 6.4) {
        return 3;
    } else if (rougness < 12.8) {
        return 2;
    } else if (rougness < 50) {
        return 1;
    }
    return 0;
}

float MechanicalStage::calculateCutDistance(unsigned step, float diameter) {
    switch (step) {
    case 0:
        if (diameter < 18) {
            return 2.0;
        } else if (diameter < 30) {
            return 2.5;
        } else if (diameter < 50) {
            return 3.0;
        } else if (diameter < 80) {
            return 3.5;
        } else if (diameter < 120) {
            return 4.5;
        } else if (diameter < 180) {
            return 5.0;
        } else if (diameter < 250) {
            return 5.5;
        } else if (diameter < 320) {
            return 6.5;
        } else if (diameter < 400) {
            return 7.5;
        }
        return 8.5;
    
    case 1:
        if (diameter < 18) {
            return 0.9;
        } else if (diameter < 30) {
            return 1.0;
        } else if (diameter < 50) {
            return 1.3;
        } else if (diameter < 80) {
            return 1.5;
        } else if (diameter < 120) {
            return 1.7;
        } else if (diameter < 180) {
            return 2.0;
        } else if (diameter < 250) {
            return 2.2;
        } else if (diameter < 320) {
            return 2.4;
        } else if (diameter < 400) {
            return 2.6;
        }
        return 2.8;

    case 3:
        if (diameter < 18) {
            return 0.5;
        } else if (diameter < 30) {
            return 0.6;
        } else if (diameter < 50) {
            return 0.7;
        } else if (diameter < 80) {
            return 0.8;
        } else if (diameter < 120) {
            return 0.9;
        } else if (diameter < 180) {
            return 1.0;
        } else if (diameter < 250) {
            return 1.1;
        } else if (diameter < 320) {
            return 1.2;
        } else if (diameter < 400) {
            return 1.4;
        }
        return 1.6;

    case 4:
        if (diameter < 30) {
            return 0.2;
        } else if (diameter < 120) {
            return 0.3;
        } else if (diameter < 400) {
            return 0.4;
        }
        return 0.6;
    }
    return 0;
}

float MechanicalStage::calculateInputDiameter(unsigned step, float outDiameter) {
    return outDiameter+2*calculateCutDistance(step, outDiameter);
}

float MechanicalStage::calculateInputLength(unsigned step, float outLength) {
    return outLength;
}

float MechanicalStage::calculateToolFeed() {
    return (inputPart.diameter/2)*sinf(Part::material.mainFi()+Part::material.addFi())/sinf(Part::material.mainFi())/sinf(Part::material.addFi());
}

float MechanicalStage::calculateCutSpeed() {
    return Part::material.Cv(calculateToolFeed()) / powf(normTimeCut, 0.4);
}

float MechanicalStage::calculateRotateFrequency() {
    return std::roundf(1000*calculateCutSpeed()/inputPart.diameter);
}

float MechanicalStage::calculateMinuteFeed() {
    return calculateToolFeed()*calculateRotateFrequency();
}

float MechanicalStage::calculateTime() {
    return (inputPart.length+2)/(calculateMinuteFeed());
}

float MechanicalStage::calculatePowerConsumption() {
    return powerInput*time;
}

// Getting public functions
Part MechanicalStage::getInputPart() {
    return inputPart;
}

float MechanicalStage::getTime() {
    return time;
}

float MechanicalStage::getPowerConsumption() {
    return powerConsumption;
}

int MechanicalStage::getNeedLathes(float settedPartCapacity) {
    return std::ceilf(settedPartCapacity*time);
}
