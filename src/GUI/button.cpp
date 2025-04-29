#include "GUI.hpp"

#include <iostream>


GUI::Button::Button(Window& win, float X, float Y, float W, float H, const std::string _text[LNG_COUNT])
: rect({W, H}),
texts(_text),
text(win.font, texts[win.language]) {
    // Creating and placing back rect
    rect.setPosition({X, Y});
    rect.setFillColor(sf::Color{120, 120, 120});
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);

    // Creating and placing text
    text.setOrigin({text.getGlobalBounds().size.x/2, text.getGlobalBounds().size.y/2+5});
    text.setPosition({X + rect.getGeometricCenter().x, Y + rect.getGeometricCenter().y});
    text.setFillColor(sf::Color::White);
}

GUI::Button::~Button() {
    
}

bool GUI::Button::isClicked(sf::Vector2i point) {
    return (rect.getPosition().x < point.x)
        && (rect.getPosition().y < point.y)
        && (rect.getPosition().x + rect.getSize().x > point.x)
        && (rect.getPosition().y + rect.getSize().y > point.y);
}

void GUI::Button::update(Window& window) {
    text.setString(texts[window.language]);
}

void GUI::Button::draw(Window& window) {
    window.draw(rect);
    window.draw(text);
}
