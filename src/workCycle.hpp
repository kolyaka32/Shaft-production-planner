#pragma once

#include "app/cycleTemplate.hpp"


// Template class for create and run cycles
class WorkCycle : public CycleTemplate {
private:
    GUI::Button button;
    GUI::Button button2;
    GUI::TypeBox typeBox;
    bool vis = true;

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
