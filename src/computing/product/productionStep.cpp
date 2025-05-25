#include "productionStep.hpp"
#include <cmath>

ProductionStep::ProductionStep(Window& window, float X, float Y, LanguagedText _text)
: background({150, 150}),
stepText(window, X+75, Y+5, _text),
diameterText(window.font),
massText(window.font) {
    background.setPosition({X, Y});
    background.setFillColor(sf::Color{120, 120, 120});
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);

    diameterText.setPosition({X, Y+50});
    massText.setPosition({X, Y+100});
}

void ProductionStep::draw(Window& window) {
    window.draw(background);
    stepText.draw(window);
    window.draw(diameterText);
    window.draw(massText);
}

void ProductionStep::setNewParameters(float _diameter, float _length, const Material material) {
    sf::String s3 = diameterText.getString();
    diameterText.setString(std::format("d={:.1f} mm", _diameter));
    massText.setString(std::format("m={:.2f} kg", _diameter*_diameter*3.141592/4*material.density*_length/1000000000));
}
