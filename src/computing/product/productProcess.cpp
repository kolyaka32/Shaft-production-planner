#include "productProcess.hpp"

float ProductProcess::targetRoughness = 10;
float ProductProcess::baseRoughness = 40;
int ProductProcess::stepCount = 4;
Material ProductProcess::material = Material::machineSteel;
unsigned ProductProcess::materialIndex = 1;


ProductProcess::ProductProcess(Window& window)
: step {
    {window,  20, 540, 40, {"Rough", "Черновая"}},
    {window, 240, 540, 20, {"Main", "Основная"}},
    {window, 460, 540, 10, {"Trimming", "Отделочная"}},
    {window, 680, 540, 10, {"Finishing", "Чистовая"}}
},
arrowTexture(resourcesDir() / "GUI/arrow.png"),
arrowSprite(arrowTexture) {
    setMaterial(materialIndex);
}

void ProductProcess::setTargetRoughness(float _targetRoughness) {
    targetRoughness = _targetRoughness;
}

void ProductProcess::setBaseRoughness(float _baseRoughness) {
    baseRoughness = _baseRoughness;
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
}

std::string ProductProcess::getTargetRoughness() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << targetRoughness;
    return oss.str();
}

std::string ProductProcess::getBaseRoughness() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << baseRoughness;
    return oss.str();
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
