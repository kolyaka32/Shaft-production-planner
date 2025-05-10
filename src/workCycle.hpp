#pragma once

#include "app/cycleTemplate.hpp"
#include "computing/factory.hpp"
#include "computing/cursorMachine.hpp"

// Template class for create and run cycles
class WorkCycle : public CycleTemplate {
private:
    // Graphic objects
    GUI::Button button1, button2, button3, button4;
    GUI::TypeBox typeBox;
    Factory factory;

    // Current selected object to place
    bool selectObject = false;
    CursorMachine cursorMachine;

protected:
    void keyDown(sf::Event::KeyPressed state) override;
    void mouseClick(sf::Vector2i pos) override;
    void mouseUnClick(sf::Vector2i pos) override;
    void textInput(char32_t keyCode) override;
    void update() override;
    void draw() override;

public:
    WorkCycle(Window& window);
    ~WorkCycle();
};
