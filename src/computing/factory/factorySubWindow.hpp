#pragma once

#include "factory.hpp"

// Subwindow for create and set parameters of factory grid
class FactorySubWindow {
private:
    // Grid options
    GUI::Text widthText, heightText;
    GUI::TypeBox widthBox, heightBox;
    GUI::TextButton cellTypeButtons[5];
    GUI::TextButton updateLinkageButton;
    Factory factory;

    // Global options
    GUI::TextButton saveButton, loadButton;
    GUI::InfoBox saveInfo;
    GUI::ImageButton languageButtons[2];

    // Current selected object to place
    bool selectObject = false;
    Cell cursorCell;

public:
    FactorySubWindow(Window& window);
    void keyDown(sf::Event::KeyPressed state);
    void LClick(Window& window, sf::Vector2i pos);
    void LUnClick(sf::Vector2i pos);
    void RClick(sf::Vector2i pos);
    void textInput(char32_t keyCode);
    void update(Window& window);
    void draw(Window& window);
    void updateLocation(Window& window);
};
