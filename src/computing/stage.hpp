#pragma once

#include "part.hpp"


// 
class Stage {
private:
    // Variables
    int capacity;
    float operationTime;  // In hours
    int requiredQuantity;
    float powerConsumption;

protected:
    void setCapacity(int capacity);
    void setOperationTime(float time);
    void setRequiredQuantity(float settedPartCapacity, int batchVolume);
    void setPowerConsumption(float powerConsumtion);

public:
    Stage();
    int getReqieredQuantity();
    int getCapacity();
    float getTimePerOperation();
    float getTimePerBatch(int batchVolume);
};
