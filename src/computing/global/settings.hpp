#pragma once

#include "../../app/cycleTemplate.hpp"


class Settings {
private:
    /* data */
    /*GUI::ImageButton languageButtons[2];*/

public:
    Settings();
    ~Settings();
    void draw(Window& window);
    bool click(sf::Vector2i pos);
};
