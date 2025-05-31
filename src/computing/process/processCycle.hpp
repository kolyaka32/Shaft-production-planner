#pragma once

#include "../global/submenuCycle.hpp"
#include "processPlanner.hpp"


// Subwindow for create and set properties of part and final product
class ProcessCycle : public SubmenuCycle {
private:
    // Main process parameters and solver
    ProcessPlanner planner;
    // Option to deal with
    GUI::Text targetInputText;
    GUI::TypeBox targetInput;

public:
    ProcessCycle(Window& window);
    void LClick(sf::Vector2i pos) override;
    void LUnClick(sf::Vector2i pos) override;
    void RClick(sf::Vector2i pos) override;
    void keyDown(sf::Event::KeyPressed state) override;
    void textInput(char32_t keyCode) override;
    void update() override;
    void draw() override;
};
