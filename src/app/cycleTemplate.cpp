#include "cycleTemplate.hpp"


CycleTemplate::CycleTemplate(Window& _window)
: window(_window) {}

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
            // Switching depend on pressed button, what to do
            switch (t->button) {
            case sf::Mouse::Button::Left:
                mouseLClick(t->position);
                break;
            
            case sf::Mouse::Button::Right:
                mouseRClick(t->position);
                break;
            }
        }
        if (auto t = event->getIf<sf::Event::MouseButtonReleased>()) {
            // Switching depend on pressed button, what to do
            switch (t->button) {
            case sf::Mouse::Button::Left:
                mouseLUnClick(t->position);
                break;

            case sf::Mouse::Button::Right:
                mouseRUnClick(t->position);
                break;
            }
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
