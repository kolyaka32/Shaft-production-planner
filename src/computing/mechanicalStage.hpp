#pragma once

#include "part.hpp"

class MechanicalStage {
private:
    // Standard tool durability time
    const float normTimeCut = 30.0;
    const float powerInput = 100;
    int stepNumber;
    Part inputPart;
    float time;
    float powerConsumption;

protected:
    float calculateCutDistance(unsigned step, float diameter);
    float calculateInputDiameter(unsigned step, float outDiameter);
    float calculateInputLength(unsigned step, float outLength);

    // Time calculation process
    float calculateToolFeed();
    float calculateCutSpeed();
    float calculateRotateFrequency();
    float calculateMinuteFeed();
    float calculateTime();

    float calculatePowerConsumption();

public:
    MechanicalStage();
    void setNew(Part outPart, float stepIndex);
    Part getInputPart();
    float getTime();
    float getPowerConsumption();
    int getNeedLathes(float settedPartCapacity);

    static int getStepNumber(float rougness);
};
