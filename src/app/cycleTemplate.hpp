#pragma once

#include "window.hpp"
#include "../GUI/GUI.hpp"


// Template class for create and run cycles
class CycleTemplate {
private:
    void getInput();  // Function for catching all input

protected:
    // Target window, where get input and draw to
    Window& window;

    // Overriding functions for do with input
    virtual void keyDown(sf::Event::KeyPressed state) {};
    virtual void mouseClick(sf::Vector2i pos) {};
    virtual void mouseUnClick(sf::Vector2i pos) {};
    virtual void textInput(char32_t keyCode) {};

    // Overring function for another objects update
    virtual void update() {};

    // Overreding function for draw data to screen
    virtual void draw() {};

public:
    CycleTemplate(Window& window);
    void run();  // Start current cycle
};
