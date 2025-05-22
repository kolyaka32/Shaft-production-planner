#include "productProcess.hpp"

float ProductProcess::targetRoughness = 10;
float ProductProcess::baseRoughness = 40;
int ProductProcess::stepCount = 2;


ProductProcess::ProductProcess(Window& window)
: step {
    {window,  20, 540, 40, {"", "Черновая"}},
    {window, 240, 540, 20, {"", "Основная"}},
    {window, 460, 540, 10, {"", "Отделочная"}},
    {window, 680, 540, 10, {"", "Чистовая"}}
},
arrowTexture(resourcesDir() / "GUI/arrow.png"),
arrowSprite(arrowTexture) {}

void ProductProcess::setTargetRoughness(float _targetRoughness) {
    targetRoughness = _targetRoughness;
}

void ProductProcess::setBaseRoughness(float _baseRoughness) {
    baseRoughness = _baseRoughness;
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

void ProductProcess::draw(Window& window) {
    arrowSprite.setPosition({175, 600});
    for (int i=0; i < stepCount; ++i) {
        step[i].draw(window);
    }
    for (int i=0; i < stepCount-1; ++i) {
        window.draw(arrowSprite);
        arrowSprite.move({200, 0});
    }
}
