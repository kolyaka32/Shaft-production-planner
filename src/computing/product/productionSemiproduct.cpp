#include "productionSemiproduct.hpp"

ProductionSemiproduct::ProductionSemiproduct(Window& window, float X, float Y)
: background({150, 150}),
diameterText(window.font),
lengthText(window.font),
massText(window.font),
rougnessText(window.font) {
    background.setPosition({X, Y});
    background.setFillColor(sf::Color{120, 120, 120});
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);

    diameterText.setPosition({X, Y});
    lengthText.setPosition({X, Y+35});
    massText.setPosition({X, Y+70});
    rougnessText.setPosition({X, Y+105});
}

void ProductionSemiproduct::draw(Window& window) {
    window.draw(background);
    window.draw(diameterText);
    window.draw(lengthText);
    window.draw(massText);
    window.draw(rougnessText);
}

void ProductionSemiproduct::setNewParameters(Part part) {
    diameterText.setString(std::format("d={:.1f} mm", part.diameter));
    lengthText.setString(std::format("l={:.0f} mm", part.length));
    massText.setString(std::format("m={:.2f} kg", part.getMass()));
    rougnessText.setString(std::format("Rz={:.1f} mkm", part.rougness));
}
