#include "productProcess.hpp"

float ProductProcess::targetRoughness = 4;
float ProductProcess::baseRoughness = 40;
int ProductProcess::stepCount = 4;
Material ProductProcess::material = Material::machineSteel;
unsigned ProductProcess::materialIndex = 1;
float ProductProcess::targetDiameter = 60;
float ProductProcess::targetLength = 200;


ProductProcess::ProductProcess(Window& window)
: step {
    {window,  20, 540, {"Rough", "Черновая"}},
    {window, 240, 540, {"Main", "Основная"}},
    {window, 460, 540, {"Trimming", "Отделочная"}},
    {window, 680, 540, {"Finishing", "Чистовая"}}
},
arrowTexture(resourcesDir() / "GUI/arrow.png"),
arrowSprite(arrowTexture) {
    setMaterial(materialIndex);
}

void ProductProcess::setTargetRoughness(float _targetRoughness) {
    targetRoughness = _targetRoughness;
    updateProcessParameters();
}

void ProductProcess::setBaseRoughness(float _baseRoughness) {
    baseRoughness = _baseRoughness;
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

std::string ProductProcess::getTargetRoughness() {
    return std::format("{:.1f}", targetRoughness);
}

std::string ProductProcess::getBaseRoughness() {
    return std::format("{:.1f}", baseRoughness);
}

std::string ProductProcess::getTargetDiameter() {
    return std::format("{:.1f}", targetDiameter);
}

std::string ProductProcess::getTargetLength() {
    return std::format("{:.0f}", targetLength);
}

unsigned ProductProcess::getMaterial() {
    return materialIndex;
}


void ProductProcess::draw(Window& window) {
    arrowSprite.setPosition({175, 600});
    for (int i=0; i < stepCount; ++i) {
        step[i].draw(window);
    }
    for (int i=0; i < stepCount-1; ++i) {
        window.draw(arrowSprite);
        arrowSprite.move({220, 0});
    }
}


void ProductProcess::updateProcessParameters() {
    // Update step count
    updateStepCount();

    // Update input diameters
    float inputDiameter = targetDiameter;
    float inputLength = targetLength;
    for (int i=stepCount-1; i >= 0; --i) {
        inputDiameter = getInputDiameter(i, inputDiameter);
        targetLength = getInputLength(i, inputLength);
        step[i].setNewParameters(inputDiameter, inputLength, material);
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
    return outLength;
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
