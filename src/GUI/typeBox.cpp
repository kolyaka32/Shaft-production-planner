#include "GUI.hpp"



GUI::TypeBox::TypeBox(Window& window, float X, float Y, float W, float H, std::string startText)
: drawText(window.font),
currentText(startText) {
    drawText.setString(currentText);
    drawText.setPosition({X, Y});
    drawText.setOrigin({0, drawText.getGlobalBounds().size.y/2});
}

GUI::TypeBox::~TypeBox() {

}

void GUI::TypeBox::click(sf::Vector2i point) {

}

void GUI::TypeBox::update(sf::Vector2i point) {

}

void GUI::TypeBox::draw(Window& window) {
    window.draw(drawText);
}
