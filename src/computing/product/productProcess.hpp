#pragma once

#include "productionStep.hpp"
#include "material.hpp"

//
class ProductProcess {
private:
    ProductionStep step[4];
    const sf::Texture arrowTexture;
    sf::Sprite arrowSprite;
    static float targetRoughness;
    static float baseRoughness;
    static int stepCount;
    static Material material;
    static unsigned materialIndex;

public:
    ProductProcess(Window& window);
    void setTargetRoughness(float targetRoughness);
    void setBaseRoughness(float baseRoughness);
    void setMaterial(unsigned index);
    std::string getTargetRoughness();
    std::string getBaseRoughness();
    unsigned getMaterial();
    void draw(Window& window);
};
