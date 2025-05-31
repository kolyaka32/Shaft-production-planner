#include <iostream>
#include "GUI.hpp"


GUI::Text::Text(Window& window, float X, float Y, LanguagedText _texts, Aligment _aligment)
: text(window.font, _texts.getUTF8()) {
    switch (_aligment) {
    case Aligment::Midle:
        text.setOrigin({text.getGlobalBounds().size.x/2, 0});
        break;

    case Aligment::Right:
        text.setOrigin({text.getGlobalBounds().size.x, 0});
        break;
    }
    text.setPosition({X, Y});
}

GUI::Text::Text(Window& window, float X, float Y, const std::string _text, Aligment _aligment)
: text(window.font, sf::String::fromUtf8(_text.begin(), _text.end())) {
    switch (_aligment) {
    case Aligment::Midle:
        text.setOrigin({text.getGlobalBounds().size.x/2, 0});
        break;

    case Aligment::Right:
        text.setOrigin({text.getGlobalBounds().size.x, 0});
        break;
    }
    text.setPosition({X, Y});
}

void GUI::Text::setText(LanguagedText texts) {
    float width = text.getGlobalBounds().size.x;
    text.setString(texts.getUTF8());
    text.setOrigin({text.getOrigin().x/width*text.getGlobalBounds().size.x, 0.0f});
}

void GUI::Text::setText(const std::string _text) {
    float width = text.getGlobalBounds().size.x;
    text.setString(sf::String::fromUtf8(_text.begin(), _text.end()));
    text.setOrigin({text.getOrigin().x/width*text.getGlobalBounds().size.x, 0.0f});
}

void GUI::Text::draw(Window& window) {
    window.draw(text);
}
