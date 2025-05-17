#include "GUI.hpp"
#include <iostream>


GUI::TextButton::TextButton(Window& win, float X, float Y, float W, float H, LanguagedText _texts)
: rect({W, H}),
texts(_texts),
text(win.font, texts.getUTF8()) {
    // Creating and placing back rect
    rect.setPosition({X, Y});
    rect.setFillColor(sf::Color{120, 120, 120});
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);

    // Creating and placing text
    text.setOrigin({text.getGlobalBounds().size.x/2, text.getGlobalBounds().size.y/2+7});
    text.setPosition({X + rect.getGeometricCenter().x, Y + rect.getGeometricCenter().y});
    text.setFillColor(sf::Color::White);
}

bool GUI::TextButton::isClicked(sf::Vector2i point) {
    return (rect.getPosition().x < point.x)
        && (rect.getPosition().y < point.y)
        && (rect.getPosition().x + rect.getSize().x > point.x)
        && (rect.getPosition().y + rect.getSize().y > point.y);
}

void GUI::TextButton::update(Window& window) {
    text.setString(texts.getUTF8());
    text.setOrigin({text.getGlobalBounds().size.x/2, text.getGlobalBounds().size.y/2+7});
}

void GUI::TextButton::draw(Window& window) {
    window.draw(rect);
    window.draw(text);
}
