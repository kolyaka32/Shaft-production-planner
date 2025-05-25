#pragma once

#include "../../app/cycleTemplate.hpp"
#include "material.hpp"


// Class showing one process step of part production
class ProductionStep {
 private:
    GUI::Text stepText;
    const sf::Texture arrowTexture;
    sf::Sprite arrowSprite;

 public:
    ProductionStep(Window& window, float X, float Y, LanguagedText text);
    void draw(Window& window);
};
