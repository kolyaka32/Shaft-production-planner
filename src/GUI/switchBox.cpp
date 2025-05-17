#include "GUI.hpp"

template <unsigned count>
GUI::SwitchBox<count>::SwitchBox(Window& window, float X, float Y, LanguagedText _texts[count]) {
    float maxWidth = 0;
    for (int i=0; i < count; ++i) {
        drawnText[i] = sf::Text(window.font, _texts[i].getString());
        drawnText[i].setPosition({X, Y+i*30+30});
        maxWidth = std::max(maxWidth, drawnText[i].getGlobalBounds().size.x);
    }
    // Setting background of active text
    backgroundBox.setSize({maxWidth, 30});
    backgroundBox.setPosition({X, Y});
}

template <unsigned count>
bool GUI::SwitchBox<count>::click(sf::Vector2i point) {
    if (opened) {
        if ((backgroundBox.getGlobalBounds().position.x < point.x)
        && (backgroundBox.getGlobalBounds().position.y < point.y)
        && (backgroundBox.getGlobalBounds().position.x + backgroundBox.getGlobalBounds().size.x > point.x)
        && (backgroundBox.getGlobalBounds().position.y + backgroundBox.getGlobalBounds().size.y > point.y)) {
            opened = true;
            backgroundBox;
        }
    } else {
        if ((backgroundBox.getGlobalBounds().position.x < point.x)
        && (backgroundBox.getGlobalBounds().position.y < point.y)
        && (backgroundBox.getGlobalBounds().position.x + backgroundBox.getGlobalBounds().size.x > point.x)
        && (backgroundBox.getGlobalBounds().position.y + backgroundBox.getGlobalBounds().size.y > point.y)) {
            // Finding new option
            selected = (point.x - backgroundBox.getGlobalBounds().position.y) / 30;

            return true;
        } else {
            opened = false;
        }
    }
}

template <unsigned count>
void GUI::SwitchBox<count>::draw(Window& window) {
    // Draw open or close version depend on state
    if (opened) {
        window.draw(backgroundBox);
        for (int i=0; i < count; ++i) {
            window.draw(drawnText[i]);
        }
    } else {
        window.draw(drawnText[selected]);
        window.draw(backgroundBox);
    }
}
