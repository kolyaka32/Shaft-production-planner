#include "GUI.hpp"



GUI::TypeBox::TypeBox(Window& window, float X, float Y, unsigned _maxLength, std::string _startText)
: maxLength(_maxLength),
drawText(window.font),
charSize(drawText.getCharacterSize()),
backGround({maxLength*(float)charSize, 20}) {
    // Setting text settings
    drawText.setFillColor(sf::Color::Black);
    drawText.setString(_startText);
    drawText.setPosition({X, Y});
    drawText.setOrigin({0, drawText.getGlobalBounds().size.y/2});

    // Setting background rect
    backGround.setPosition({X, Y});
    backGround.setFillColor(sf::Color::White);
    backGround.setOutlineThickness(2);
    backGround.setOutlineColor(sf::Color::Black);
}

GUI::TypeBox::~TypeBox() {

}

void GUI::TypeBox::click(sf::Vector2i point) {
    // Checking, if pressed to start typing
    if (backGround.getLocalBounds().contains({(float)point.x, (float)point.y})) {
        selected = true;
        pressed = true;

        // Finding selection start point
        caret = (point.x - drawText.findCharacterPos(0).x) / charSize;
        selectLength = 0;
        showCaret = true;
        clock.restart();
    } else {
        selected = false;
        pressed = false;
    }
}

void GUI::TypeBox::unClick() {
    pressed = false;
    showCaret = false;
}

void GUI::TypeBox::keyPress(sf::Event::KeyPressed state) {

}

void GUI::TypeBox::inputText(char32_t ch) {
    //drawText.getString().substring();
}

void GUI::TypeBox::update(sf::Vector2i point) {
    if (selected) {
        // Che
        if (pressed) {
            // Getting new selection length
            caret = (point.x - drawText.findCharacterPos(0).x) / charSize;
            drawCaret.setPosition({(float)point.x, backGround.getPosition().x});
        }
        // Blinking caret
        if (clock.getElapsedTime().asSeconds() > 2) {
            showCaret ^= true;
            updateTime = clock.restart();
        }
    }
}

void GUI::TypeBox::draw(Window& window) {
    window.draw(backGround);
    window.draw(drawText);
    if (showCaret) {
        window.draw(drawCaret);
    }
}

// Getting result
std::string GUI::TypeBox::getString() {
    return drawText.getString();
}

float GUI::TypeBox::getNumber() {
    return std::stoi((std::string)drawText.getString());
    // At this moment - simple function
    // TODO: create improved parser for understand +-*/()^
}
