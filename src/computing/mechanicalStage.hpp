#pragma once

#include "part.hpp"

class MechanicalStage {
private:
    // Standard tool durability time
    const float normTimeCut = 30.0;  // In minutes
    const float powerInput = 1.5;    // In kilowatts
    Part inputPart;
    float time;  // In hours
    int requiredQuantity;
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
    void set(Part outPart, unsigned stepIndex, float settedPartCapacity);
    void setFirst(Part outPart, unsigned stepIndex, float settedPartCapacity, float inputRougness);
    Part getInputPart();
    float getTimePerOperation();
    float getTimePerUnit();
    float getPowerConsumption();
    int getNeedLathes();

    static int getStepNumber(float rougness);
    static float getRougness(int stepIndex);
};
