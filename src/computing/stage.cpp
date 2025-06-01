#include "stage.hpp"


Stage::Stage() {}

void Stage::setCapacity(int _capacity) {
    capacity = _capacity;
}

void Stage::setOperationTime(float _time) {
    operationTime = _time;
}

void Stage::setRequiredQuantity(float _settedPartCapacity, int _batchVolume) {
    requiredQuantity = std::ceilf(_settedPartCapacity*operationTime/capacity);
    // Check, if produce less parts than required
    if (requiredQuantity > _batchVolume) {
        requiredQuantity = _batchVolume;
    }
}

void Stage::setPowerConsumption(float _powerConsumtion) {
    powerConsumption = _powerConsumtion;
}

int Stage::getReqieredQuantity() {
    return requiredQuantity;
}

int Stage::getCapacity() {
    return capacity;
}

float Stage::getTimePerOperation() {
    return operationTime;
}

float Stage::getTimePerBatch(int _batchVolume) {
    return ceilf((float)ceilf((float)_batchVolume/capacity)/requiredQuantity)*operationTime;
}
