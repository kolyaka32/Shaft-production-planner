#pragma once

#include "productionStep.hpp"
#include "../part.hpp"

//
class ProductionSemiproduct {
 private:
    sf::RectangleShape background;
    sf::Text diameterText;
    sf::Text massText;
    sf::Text lengthText;
    sf::Text rougnessText;

 public:
    ProductionSemiproduct(Window& window, float X, float Y);
    void draw(Window& window);
    void setNewParameters(Part part);
};
