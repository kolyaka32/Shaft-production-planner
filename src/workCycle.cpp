#include "workCycle.hpp"

#include <iostream>

WorkCycle::WorkCycle(Window& window)
: CycleTemplate(window),
button(window, 100.f, 200.f, 100.f, 50.f, {"123456789", "Abc"}),
button2(window, 200, 400, 50, 50, {"lan1", "lan2"}),
typeBox(window, 300, 100, 500, 100, "ABC") {

}

WorkCycle::~WorkCycle() {

}

void WorkCycle::keyDown(sf::Event::KeyPressed state) {
    
}

void WorkCycle::mouseClick(sf::Vector2i pos) {
    if (button.isClicked(pos)) {
        vis = vis ^ true;
    }
    if (button2.isClicked(pos)) {
        if (window.language == LNG_ENGLISH) {
            window.language = LNG_RUSSIAN;
        } else {
            window.language = LNG_ENGLISH;
        }
        button.update(window);
        button2.update(window);
    }
}

void WorkCycle::mouseUnClick(sf::Vector2i pos) {

}

void WorkCycle::textInput(char32_t keyCode) {
    std::cout << (int)keyCode;
}

void WorkCycle::update() {

}

void WorkCycle::draw() {
    // Clear the window
    window.clear(sf::Color(20, 20, 20));

    button.draw(window);

    button2.draw(window);

    if (vis) {
        typeBox.draw(window);
    }

    // Display things on screen
    window.display();
}
