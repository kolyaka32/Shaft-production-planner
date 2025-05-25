#pragma once

#include <string>
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
    static Material material;
    static unsigned materialIndex;
    static float targetDiameter;
    static float targetLength;

 protected:
    static float getCutRoughDistance(float diameter);
    static float getCutMainDistance(float diameter);
    static float getCutTrimmingDistance(float diameter);
    static float getCutFinishingDistance(float diameter);
    float getInputDiameter(unsigned step, float outDiameter);
    float getInputLength(unsigned step, float outLength);
    void updateProcessParameters();
    void updateStepCount();

 public:
    ProductProcess(Window& window);
    void setTargetRoughness(float targetRoughness);
    void setBaseRoughness(float baseRoughness);
    void setMaterial(unsigned index);
    void setTargetDiameter(float length);
    void setTargetLength(float length);
    std::string getTargetRoughness();
    std::string getBaseRoughness();
    std::string getTargetLength();
    std::string getTargetDiameter();
    unsigned getMaterial();
    void draw(Window& window);
};
