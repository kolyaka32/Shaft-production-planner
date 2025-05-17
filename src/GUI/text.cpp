#include "GUI.hpp"

#include <iostream>

GUI::Text::Text(Window& window, float X, float Y, LanguagedText _texts)
: texts(_texts),
text(window.font, texts.getUTF8()) {
    text.setOrigin({text.getGlobalBounds().size.x/2, 0});
    text.setPosition({X, Y});
}

void GUI::Text::update(Window& window) {
    text.setString(texts.getUTF8());
    auto k1 = texts.getString();
    auto k2 = texts.getUTF8();
    auto k3 = (std::string)text.getString();
    text.setOrigin({text.getGlobalBounds().size.x/2, 0});
}

void GUI::Text::draw(Window& window) {
    window.draw(text);
}
