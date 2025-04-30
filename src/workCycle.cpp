#include "workCycle.hpp"


WorkCycle::WorkCycle(Window& window)
: button(window, 100.f, 200.f, 100.f, 50.f, {"123456789", "Abc"}),
button2(window, 200, 400, 50, 50, {"lan1", "lan2"}),
typeBox(window) {

}

WorkCycle::~WorkCycle() {

}

void WorkCycle::keyDown(sf::Keyboard::Key key, Window& window) {
    
}

void WorkCycle::mouseClick(Window& window) {
    // Getting mouse position
    sf::Vector2i pos = sf::Mouse::getPosition(window);

    if (button.isClicked(pos)) {
        //
        //mouseUnClick();
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

void WorkCycle::mouseUnClick(Window& window) {

}

void WorkCycle::update(Window& window) {

}

void WorkCycle::draw(Window& window) {
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
