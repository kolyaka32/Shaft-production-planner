#pragma once

#include "../../app/cycleTemplate.hpp"
#include "settings.hpp"


//
class SubmenuCycle : public CycleTemplate {
protected:
    // Buttons for switch between subwindows
    GUI::TextButton selectProductButton, selectFactoryButton;
    // Global settings
    Settings settings;

public:
    SubmenuCycle(Window& window);
};
