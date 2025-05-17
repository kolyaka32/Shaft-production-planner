#pragma once

#include "../../GUI/GUI.hpp"


// Subwindow for create and set properties of part and final product
class ProductSubWindow {
private:
    GUI::ImageButton partPicture;
    GUI::TypeBox widthInput, heightInput;

public:
    ProductSubWindow(Window& window);
    void LClick(Window& window, sf::Vector2i pos);
    void LUnClick(sf::Vector2i pos);
    void RClick(sf::Vector2i pos);
    void keyDown(sf::Event::KeyPressed state);
    void textInput(char32_t keyCode);
    void update(Window& window);
    void draw(Window& window);
};
