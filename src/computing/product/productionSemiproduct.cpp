#include "productionSemiproduct.hpp"

ProductionSemiproduct::ProductionSemiproduct(Window& window, float X, float Y)
: background({150, 150}),
diameterText(window.font),
lengthText(window.font),
massText(window.font) {
    background.setPosition({X, Y});
    background.setFillColor(sf::Color{120, 120, 120});
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);

    diameterText.setPosition({X, Y+20});
    lengthText.setPosition({X, Y+60});
    massText.setPosition({X, Y+100});
}

void ProductionSemiproduct::draw(Window& window) {
    window.draw(background);
    window.draw(diameterText);
    window.draw(lengthText);
    window.draw(massText);
}

void ProductionSemiproduct::setNewParameters(float _diameter, float _length, const Material material) {
    diameterText.setString(std::format("d={:.1f} mm", _diameter));
    lengthText.setString(std::format("l={:.0f} mm", _length));
    massText.setString(std::format("m={:.2f} kg", _diameter*_diameter*3.141592/4*material.density*_length/1000000000));
}
