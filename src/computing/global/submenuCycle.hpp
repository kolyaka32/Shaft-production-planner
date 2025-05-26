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
    // Saving options
    GUI::TextButton saveButton, loadButton;
    GUI::InfoBox saveInfo;
    void save();
    void load();

 public:
    SubmenuCycle(Window& window);
};
