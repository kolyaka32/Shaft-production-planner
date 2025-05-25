#include "productProcess.hpp"


// Static global process options

int ProductProcess::stepCount = 4;
Material ProductProcess::material = Material::machineSteel;
unsigned ProductProcess::materialIndex = 1;
float ProductProcess::targetRoughness = 4;
float ProductProcess::targetDiameter = 60;
float ProductProcess::targetLength = 200;
float ProductProcess::blankRoughness = 40;
float ProductProcess::blankDiameter = 80;
float ProductProcess::blankLength = 220;


ProductProcess::ProductProcess(Window& window)
: semiproducts {
    {window,  20, 540},
    {window, 250, 540},
    {window, 480, 540},
    {window, 710, 540},
    {window, 940, 540}},
steps {
    {window, 170, 540, {"Rough", "Черновая"}},
    {window, 400, 540, {"Main", "Основная"}},
    {window, 630, 540, {"Trimming", "Отделочная"}},
    {window, 860, 540, {"Finishing", "Чистовая"}}},
warningLowLength(window, 750, 300, {"Insufficient length", "Недостаточная длинна"}, "machines/danger-icon.png"),
warningLowDiameter(window, 750, 350, {"Insufficient diameter", "Недостаточный диаметр"}, "machines/danger-icon.png"),
warningHighLength(window, 750, 300, {"Redundant length", "Избыточная длинна"}, "machines/warning-icon.png"),
warningHighDiameter(window, 750, 350, {"Redundant diameter", "Избыточный диаметр"}, "machines/warning-icon.png") {
    setMaterial(materialIndex);
}

void ProductProcess::setTargetRoughness(float _targetRoughness) {
    targetRoughness = _targetRoughness;
    updateProcessParameters();
}

void ProductProcess::setTargetDiameter(float _targetDiameter) {
    targetDiameter = _targetDiameter;
    updateProcessParameters();
}

void ProductProcess::setTargetLength(float _targetLength) {
    targetLength = _targetLength;
    updateProcessParameters();
}

void ProductProcess::setBlankRoughness(float _roughness) {
    blankRoughness = _roughness;
    updateProcessParameters();
}

void ProductProcess::setBlankLength(float _length) {
    blankLength = _length;
    updateProcessParameters();
}

void ProductProcess::setBlankDiameter(float _diameter) {
    blankDiameter = _diameter;
    updateProcessParameters();
}

void ProductProcess::setMaterial(unsigned index) {
    switch (index) {
    case 1:
        material = Material::machineSteel;
        break;

    case 2:
        material = Material::alloys;
        break;

    case 3:
        material = Material::heatResistantSteel;
        break;
    }
    updateProcessParameters();
}

unsigned ProductProcess::getMaterial() {
    return materialIndex;
}

std::string ProductProcess::getTargetRoughness() {
    return std::format("{:.1f}", targetRoughness);
}

std::string ProductProcess::getTargetLength() {
    return std::format("{:.0f}", targetLength);
}

std::string ProductProcess::getTargetDiameter() {
    return std::format("{:.1f}", targetDiameter);
}

std::string ProductProcess::getBlankRoughness() {
    return std::format("{:.1f}", blankRoughness);
}

std::string ProductProcess::getBlankLength() {
    return std::format("{:.0f}", blankLength);
}

std::string ProductProcess::getBlankDiameter() {
    return std::format("{:.1f}", blankDiameter);
}


void ProductProcess::draw(Window& window) {
    // Draw main steps
    for (int i=0; i <= stepCount; ++i) {
        semiproducts[i].draw(window);
    }
    for (int i=0; i < stepCount; ++i) {
        steps[i].draw(window);
    }
    // Draw warnings
    warningLowLength.draw(window);
    warningLowDiameter.draw(window);
    warningHighLength.draw(window);
    warningHighDiameter.draw(window);
}


void ProductProcess::updateProcessParameters() {
    // Resetting warnings
    warningLowLength.deactivate();
    warningLowDiameter.deactivate();
    warningHighLength.deactivate();
    warningHighDiameter.deactivate();

    // Update step count
    updateStepCount();

    // Update input diameters
    float inputDiameter = targetDiameter;
    float inputLength = targetLength;
    for (int i=stepCount; i > 0; --i) {
        semiproducts[i].setNewParameters(inputDiameter, inputLength, material);
        inputDiameter = getInputDiameter(i, inputDiameter);
        inputLength = getInputLength(i, inputLength);
    }
    // Update extra blank object
    semiproducts[0].setNewParameters(inputDiameter, inputLength, material);

    // Checking, if blank parameters allowable and optimal
    if (inputLength > blankLength) {
        warningLowLength.activate();
    } else if (blankLength > inputLength*1.2) {
        warningHighLength.activate();
    }
    if (inputDiameter > blankDiameter) {
        warningLowDiameter.activate();
    } else if (blankDiameter > inputDiameter*1.2) {
        warningHighDiameter.activate();
    }
}

void ProductProcess::updateStepCount() {
    if (targetRoughness < 6.4) {
        stepCount = 4;
    } else if (targetRoughness < 12.8) {
        stepCount = 3;
    } else if (targetRoughness < 50) {
        stepCount = 2;
    } else {
        stepCount = 1;
    }
}

float ProductProcess::getInputDiameter(unsigned step, float outDiameter) {
    switch (step) {
    case 4:
        return outDiameter+2*getCutFinishingDistance(outDiameter);

    case 3:
        return outDiameter+2*getCutTrimmingDistance(outDiameter);

    case 2:
        return outDiameter+2*getCutMainDistance(outDiameter);

    default:
        return outDiameter+2*getCutRoughDistance(outDiameter);
    }
}

float ProductProcess::getInputLength(unsigned step, float outLength) {
    switch (step) {
    case 4:
        return outLength+getCutFinishingDistance(outLength);

    case 3:
        return outLength+getCutTrimmingDistance(outLength);

    case 2:
        return outLength+getCutMainDistance(outLength);

    default:
        return outLength+getCutRoughDistance(outLength);
    }
}


float ProductProcess::getCutRoughDistance(float diameter) {
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
    }
    return 7.5;
}

float ProductProcess::getCutMainDistance(float diameter) {
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
    }
    return 2.6;
}

float ProductProcess::getCutTrimmingDistance(float diameter) {
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
    }
    return 1.4;
}

float ProductProcess::getCutFinishingDistance(float diameter) {
    if (diameter < 30) {
        return 0.2;
    } else if (diameter < 120) {
        return 0.3;
    } else if (diameter < 250) {
        return 0.4;
    }
    return 0.5;
}
