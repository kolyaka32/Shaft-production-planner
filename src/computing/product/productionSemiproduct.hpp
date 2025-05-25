#pragma once

#include "productionStep.hpp"

//
class ProductionSemiproduct {
 private:
    sf::RectangleShape background;
    sf::Text diameterText;
    sf::Text massText;
    sf::Text lengthText;

 public:
    ProductionSemiproduct(Window& window, float X, float Y);
    void draw(Window& window);
    void setNewParameters(float diameter, float length, const Material material);
};
