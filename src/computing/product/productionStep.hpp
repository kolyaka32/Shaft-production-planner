#pragma once

#include "../../app/cycleTemplate.hpp"
#include "material.hpp"


// Class showing one process step of part production
class ProductionStep {
 private:
    sf::RectangleShape background;
    GUI::Text stepText;
    sf::Text diameterText;
    sf::Text massText;

 public:
    ProductionStep(Window& window, float X, float Y, LanguagedText text);
    void draw(Window& window);
    void setNewParameters(float diameter, float length, const Material material);
};
