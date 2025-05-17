#pragma once

#include "../global/submenuCycle.hpp"

// Subwindow for create and set properties of part and final product
class ProductCycle : public SubmenuCycle {
private:
    GUI::ImageButton partPicture;
    GUI::TypeBox widthInput, heightInput;
    GUI::Text materialText;
    GUI::SwitchBox<3> materialSwitch;

public:
    ProductCycle(Window& window);
    void LClick(sf::Vector2i pos) override;
    void LUnClick(sf::Vector2i pos) override;
    void RClick(sf::Vector2i pos) override;
    void keyDown(sf::Event::KeyPressed state) override;
    void textInput(char32_t keyCode) override;
    void update() override;
    void draw() override;
};
