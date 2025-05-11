#include "GUI.hpp"


GUI::Text::Text(Window& window, float X, float Y, const std::vector<std::string> _texts)
: texts(_texts),
text(window.font, texts[window.language]) {
    text.setOrigin({text.getGlobalBounds().size.x/2, text.getGlobalBounds().size.y/2+5});
    text.setPosition({X, Y});
}

GUI::Text::~Text() {}

void GUI::Text::update(Window& window) {
    text.setString(texts[window.language]);
    text.setOrigin({text.getGlobalBounds().size.x/2, text.getGlobalBounds().size.y/2+5});
}

void GUI::Text::draw(Window& window) {
    window.draw(text);
}
