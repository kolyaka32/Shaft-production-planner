#include "cycleTemplate.hpp"


CycleTemplate::CycleTemplate(Window& _window)
: window(_window) {

}

void CycleTemplate::getInput() {
    // Handling events
    while (const std::optional event = window.pollEvent()) {
        // Window closed: exit
        if (event->is<sf::Event::Closed>()) {
            window.close();
            break;
        }

        // Catching pressing keys
        if (auto t = event->getIf<sf::Event::KeyPressed>()) {
            keyDown(*t);
        }
        // Catching clicking and unclicking at mouse
        if (auto t = event->getIf<sf::Event::MouseButtonPressed>()) {
            mouseClick(t->position);
        }
        if (auto t = event->getIf<sf::Event::MouseButtonReleased>()) {
            mouseUnClick(t->position);
        }
        // Catching clicking and unclicking at mouse
        if (auto t = event->getIf<sf::Event::TextEntered>()) {
            textInput(t->unicode);
        }
    }
}

void CycleTemplate::run() {
    while (window.isOpen()) {
        getInput();
        update();
        draw();
    }
}
