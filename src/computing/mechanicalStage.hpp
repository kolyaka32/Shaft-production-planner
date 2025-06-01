#pragma once

#include "stage.hpp"

class MechanicalStage : public Stage {
private:
    // Standard tool durability time
    const float normTimeCut = 30.0;  // In minutes
    const float powerInput = 1.5;    // In kilowatts

    // Variables
    Part inputPart;
    float activeTime;

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
    void set(Part outPart, unsigned stepIndex, float settedPartCapacity, int batchVolume);
    void setFirst(Part outPart, unsigned stepIndex, float inputRougness, float settedPartCapacity, int batchVolume);
    Part getInputPart();

    static int getStepNumber(float rougness);
    static float getRougness(int stepIndex);
};
