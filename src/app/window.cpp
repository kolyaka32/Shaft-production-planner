#include "window.hpp"


Window::Window(unsigned _width, unsigned _height, std::string _name)
: RenderWindow(sf::VideoMode({_width, _height}), _name),
font(resourcesDir() / "Arial.ttf") {
    // Setting frame limit
    setFramerateLimit(60);
}

Window::~Window() {}
