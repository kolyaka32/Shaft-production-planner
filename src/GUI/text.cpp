#include "GUI.hpp"


GUI::Text::Text(Window& window, float X, float Y, const std::vector<std::string> _texts)
: texts(_texts),
text(window.font, sf::String::fromUtf8(texts[window.language].begin(), texts[window.language].end())) {
    text.setOrigin({text.getGlobalBounds().size.x/2, 0});
    text.setPosition({X, Y});
}

void GUI::Text::update(Window& window) {
    text.setString(sf::String::fromUtf8(texts[window.language].begin(), texts[window.language].end()));
    text.setOrigin({text.getGlobalBounds().size.x/2, 0});
}

void GUI::Text::draw(Window& window) {
    window.draw(text);
}
