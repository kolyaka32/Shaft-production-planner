#pragma once

#include "app/cycleTemplate.hpp"
#include "computing/factory.hpp"


// Template class for create and run cycles
class WorkCycle : public CycleTemplate {
private:
    // Grid options
    GUI::Text widthText, heightText;
    GUI::TypeBox widthBox, heightBox;
    GUI::TextButton cellTypeButtons[4];
    Factory factory;

    // Global options
    GUI::TextButton saveButton, loadButton;
    GUI::InfoBox saveInfo;
    GUI::ImageButton languageButtons[2];

    // Current selected object to place
    bool selectObject = false;
    Cell cursorCell;

protected:
    void keyDown(sf::Event::KeyPressed state) override;
    void mouseLClick(sf::Vector2i pos) override;
    void mouseLUnClick(sf::Vector2i pos) override;
    void mouseRClick(sf::Vector2i pos) override;
    void textInput(char32_t keyCode) override;
    void update() override;
    void draw() override;
    void updateAll();

public:
    WorkCycle(Window& window);
};
