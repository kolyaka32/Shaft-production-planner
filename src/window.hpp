#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "testing.hpp"


// Selectable languages to use
enum LNG_types {
    LNG_ENGLISH,
    LNG_RUSSIAN,

    // Counter of all languages
    LNG_COUNT,

    // Standart pre-selected language
    LNG_DEFAULT = LNG_ENGLISH,
};


// Class with all
class Window : public sf::RenderWindow {
public:
    const sf::Font font;
    unsigned language = LNG_DEFAULT;
    
public:
    Window(unsigned width, unsigned height, std::string name);
    ~Window();
};
