#include "GUI.hpp"


GUI::InfoBox::InfoBox(Window& window, float X, float Y, const std::vector<std::string> _texts)
: texts(_texts),
text(window.font, sf::String::fromUtf8(texts[window.language].begin(), texts[window.language].end())) {
    // Setting position
    text.setOrigin({text.getGlobalBounds().size.x/2, 0});
    text.setPosition({X, Y});
}

void GUI::InfoBox::draw(Window& window) {
    // Drawing, until counter reach 0
    if (counter) {
        // Setting text to be less and less visible
        color.a = ((float)counter/100*255);
        text.setFillColor(color);
        window.draw(text);
        counter--;
    }
}

void GUI::InfoBox::update(Window& window) {
    // Changing location
    text.setString(sf::String::fromUtf8(texts[window.language].begin(), texts[window.language].end()));
    text.setOrigin({text.getGlobalBounds().size.x/2, 0});
}

void GUI::InfoBox::reset() {
    counter = 100;
}
