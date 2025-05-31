#include <cmath>
#include "mechanicalStage.hpp"


MechanicalStage::MechanicalStage() {}

void MechanicalStage::set(Part outPart, unsigned _stepNumber, float _settedPartCapacity) {
    inputPart = {calculateInputDiameter(_stepNumber, outPart.diameter), calculateInputLength(_stepNumber, outPart.length), getRougness(_stepNumber)};
    time = calculateTime();
    requiredQuantity = std::ceilf(_settedPartCapacity*time);
    powerConsumption = calculatePowerConsumption();
}

void MechanicalStage::setFirst(Part outPart, unsigned _stepNumber, float _settedPartCapacity, float _inputRougness) {
    inputPart = {calculateInputDiameter(_stepNumber, outPart.diameter), calculateInputLength(_stepNumber, outPart.length), _inputRougness};
    time = calculateTime();
    requiredQuantity = std::ceilf(_settedPartCapacity*time);
    powerConsumption = calculatePowerConsumption();
}

int MechanicalStage::getStepNumber(float rougness) {
    if (rougness <= 6.4) {
        return 3;
    } else if (rougness <= 12.8) {
        return 2;
    } else if (rougness <= 50) {
        return 1;
    }
    return 0;
}

float MechanicalStage::getRougness(int stepIndex) {
    switch (stepIndex) {
    case 0:
        return 200;

    case 1:
        return 50;
    
    case 2:
        return 12.8;

    case 3:
        return 6.4;
    }
    return 200;
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

    case 2:
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

    case 3:
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
    auto t = (inputPart.rougness/1000)*sinf(Part::material.mainFi()+Part::material.addFi())/sinf(Part::material.mainFi())/sinf(Part::material.addFi());
    return t;
}

float MechanicalStage::calculateCutSpeed() {
    auto t = Part::material.Cv(calculateToolFeed()) / powf(normTimeCut, 0.4);
    return t;
}

float MechanicalStage::calculateRotateFrequency() {
    auto t = std::roundf(1000*calculateCutSpeed()/inputPart.diameter);
    return t;
}

float MechanicalStage::calculateMinuteFeed() {
    auto t = calculateToolFeed()*calculateRotateFrequency();
    return t;
}

float MechanicalStage::calculateTime() {
    auto t = (inputPart.length+2)/(calculateMinuteFeed());
    return t;
}

float MechanicalStage::calculatePowerConsumption() {
    return powerInput*time;
}

// Getting public functions
Part MechanicalStage::getInputPart() {
    return inputPart;
}

float MechanicalStage::getTimePerOperation() {
    return time;
}

float MechanicalStage::getTimePerUnit() {
    return time/requiredQuantity;
}

float MechanicalStage::getPowerConsumption() {
    return powerConsumption;
}

int MechanicalStage::getNeedLathes() {
    return requiredQuantity;
}
