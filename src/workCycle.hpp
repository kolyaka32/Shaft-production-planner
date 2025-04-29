#pragma once

#include "cycleTemplate.hpp"


// Template class for create and run cycles
class WorkCycle : public CycleTemplate {
private:
    GUI::Button button;
    //GUI::Button button2;
    GUI::TypeBox typeBox;
    bool vis = true;

protected:
    void keyDown(sf::Keyboard::Key key, Window& window) override;
    void mouseClick(Window& window) override;
    void mouseUnClick(Window& window) override;
    void update(Window& window) override;
    void draw(Window& window) override;

public:
    WorkCycle(Window& window);
    ~WorkCycle();
};
