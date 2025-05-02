#include "GUI.hpp"

#include <iostream>

GUI::TypeBox::TypeBox(Window& window, float X, float Y, unsigned _maxLength, std::string _startText)
: maxLength(_maxLength),
charSize(19),
drawText(window.font, _startText, 30),
backGround({maxLength*(float)charSize, 30}),
inverseText(window.font, "", 30),
inverseRect() {
    // Setting text settings
    drawText.setFillColor(sf::Color::Black);
    drawText.setString(_startText);
    drawText.setPosition({X, Y});
    drawText.setOrigin({-4, drawText.getGlobalBounds().size.y/2-6});

    // Setting background rect
    backGround.setPosition({X, Y});
    backGround.setFillColor(sf::Color::White);
    backGround.setOutlineThickness(2);
    backGround.setOutlineColor(sf::Color::Black);

    // Setting blinking caret
    drawCaret.setFillColor(sf::Color{70});
    drawCaret.setSize({2.f, 30.f});
    drawCaret.setOrigin({1.f, -4.f});

    // Setting inverse selection box
    inverseText.setFillColor(sf::Color::White);
    inverseRect.setOrigin({-4, 0});

    inverseRect.setFillColor(sf::Color::Black);
    inverseRect.setOrigin({0, -4.f});
}

GUI::TypeBox::~TypeBox() {

}

bool GUI::TypeBox::in(sf::Vector2i point) {
    return (backGround.getPosition().x < point.x)
        && (backGround.getPosition().y < point.y)
        && (backGround.getPosition().x + backGround.getSize().x > point.x)
        && (backGround.getPosition().y + backGround.getSize().y > point.y);
}

void GUI::TypeBox::click(sf::Vector2i point) {
    // Checking, if pressed to start typing
    if (in(point)) {
        selected = true;
        pressed = true;

        // Finding selection start point
        caret = (point.x - (int)drawText.findCharacterPos(0).x) / charSize;
        // Setting maximal caret position
        SET_MAX(caret, drawText.getString().getSize());

        selectLength = 0;
        showCaret = true;
        clock.restart();
    } else {
        selected = false;
        pressed = false;
        selectLength = 0;
        showCaret = false;
        clock.stop();
    }
}

void GUI::TypeBox::unClick() {
    pressed = false;
}

void GUI::TypeBox::keyPress(sf::Event::KeyPressed state) {

}

void GUI::TypeBox::inputText(char32_t ch) {
    //drawText.getString().substring();
}

void GUI::TypeBox::update(sf::Vector2i point) {
    if (selected) {
        if (pressed) {
            // Getting new caret position and selection length
            selectLength += caret;
            if (point.x < backGround.getGlobalBounds().position.x) {
                caret = 0;
            } else {
                caret = (point.x - (int)drawText.findCharacterPos(0).x) / charSize;
            }
            // Setting maximal caret position
            SET_MAX(caret, drawText.getString().getSize());
            // Setting minimal caret position
            SET_MIN(caret, 0);
            selectLength -= caret;

            // Update caret position
            drawCaret.setPosition(drawText.findCharacterPos(caret));
            // Update inverse rect and text
            if (selectLength > 0) {
                inverseRect.setSize({selectLength*float(charSize), 30.f});
                inverseRect.setPosition({drawCaret.getPosition().x, drawCaret.getPosition().y});

                inverseText.setString(drawText.getString().substring(caret, selectLength));
                inverseText.setPosition(inverseRect.getPosition());
            } else {
                inverseRect.setSize({-selectLength*float(charSize), 30.f});
                std::cout << drawCaret.getPosition().x + selectLength*charSize << ' ' << drawCaret.getPosition().y << '\n';
                inverseRect.setPosition({drawCaret.getPosition().x + selectLength*charSize, drawCaret.getPosition().y});

                inverseText.setString(drawText.getString().substring(caret + selectLength, -selectLength));
                inverseText.setPosition(inverseRect.getPosition());
            }
        }
        // Blinking caret
        if (clock.getElapsedTime().asSeconds() > 1) {
            showCaret ^= true;
            updateTime = clock.restart();
        }
    }
}

void GUI::TypeBox::draw(Window& window) {
    window.draw(backGround);
    window.draw(drawText);
    if (selectLength) {
        // Inversing color in rect
        window.draw(inverseRect);
        window.draw(inverseText);
    }
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
