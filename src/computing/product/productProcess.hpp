#pragma once

#include "productionStep.hpp"


//
class ProductProcess {
private:
    ProductionStep step[4];
    const sf::Texture arrowTexture;
    sf::Sprite arrowSprite;
    static float targetRoughness;
    static float baseRoughness;
    static int stepCount;

public:
    ProductProcess(Window& window);
    void setTargetRoughness(float targetRoughness);
    void setBaseRoughness(float baseRoughness);
    std::string getTargetRoughness();
    std::string getBaseRoughness();
    void draw(Window& window);
};
