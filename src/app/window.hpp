#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../testing.hpp"
#include "macroses.hpp"
#include "languages.hpp"


// Class with all
class Window : public sf::RenderWindow {
public:
    const sf::Font font;
    unsigned language = LNG_DEFAULT;
    
public:
    Window(unsigned width, unsigned height, std::string name);
    ~Window();
};
