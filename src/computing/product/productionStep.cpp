#include "productionStep.hpp"

ProductionStep::ProductionStep(Window& window, float X, float Y, float checkRougness, LanguagedText _text)
: background({150, 150}),
stepText(window, X+75, Y+5, _text) {
    background.setPosition({X, Y});
    background.setFillColor(sf::Color{120, 120, 120});
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);
    roughness = checkRougness;
}

void ProductionStep::setNew(float _roughness) {
    roughness = _roughness;
}

void ProductionStep::draw(Window& window) {
    window.draw(background);
    stepText.draw(window);
}
