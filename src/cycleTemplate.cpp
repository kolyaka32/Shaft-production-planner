#include "cycleTemplate.hpp"


CycleTemplate::CycleTemplate() {

}

CycleTemplate::~CycleTemplate() {

}

void CycleTemplate::getInput(Window& window) {
    // Handle events
    while (const std::optional event = window.pollEvent()) {
        // Window closed: exit
        if (event->is<sf::Event::Closed>()) {
                window.close();
                break;
            }

        // Catching pressing keys
        if (event->is<sf::Event::KeyPressed>()) {
            keyDown(event->getIf<sf::Event::KeyPressed>()->code, window);
        }
        if (event->is<sf::Event::MouseButtonPressed>()) {
            mouseClick(window);
        }
        if (event->is<sf::Event::MouseButtonReleased>()) {
            mouseUnClick(window);
        }
    }
}

void CycleTemplate::run(Window& window) {
    while (window.isOpen()) {
        getInput(window);
        update(window);
        draw(window);
    }
}
