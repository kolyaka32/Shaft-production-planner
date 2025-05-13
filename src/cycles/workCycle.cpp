#include "workCycle.hpp"


WorkCycle::WorkCycle(Window& window)
: CycleTemplate(window),
factory(window),
product(window),
selectProductButton(window, 0, 0, 160, 50, {"Product", "Изделие"}),
selectFactoryButton(window, 160, 0, 160, 50, {"Factory", "Цех"}) {}

void WorkCycle::keyDown(sf::Event::KeyPressed state) {
    switch (target) {
    case currentWindow::Product:
        //product.keyDown(state);
        break;
    
    case currentWindow::Factory:
        factory.keyDown(state);
        break;
    }
}

void WorkCycle::mouseLClick(sf::Vector2i pos) {
    // First - check on switching subwindows
    if (selectProductButton.isClicked(pos)) {
        target = currentWindow::Product;
    } else if (selectFactoryButton.isClicked(pos)) {
        target = currentWindow::Factory;
    } else {
        switch (target) {
        case currentWindow::Product:
            //product.LClick(window, pos);
            break;
        
        case currentWindow::Factory:
            factory.LClick(window, pos);
            break;
        }
    }
}

void WorkCycle::mouseLUnClick(sf::Vector2i pos) {
    switch (target) {
    case currentWindow::Product:
        //product.LUnClick(pos);
        break;
    
    case currentWindow::Factory:
        factory.LUnClick(pos);
        break;
    }
}

void WorkCycle::mouseRClick(sf::Vector2i pos) {
    switch (target) {
    case currentWindow::Product:
        //product.RClick(pos);
        break;
    
    case currentWindow::Factory:
        factory.RClick(pos);
        break;
    }
}

void WorkCycle::textInput(char32_t keyCode) {
    switch (target) {
    case currentWindow::Product:
        //product.textInput(keyCode);
        break;
    
    case currentWindow::Factory:
        factory.textInput(keyCode);
        break;
    }
}

void WorkCycle::update() {
    switch (target) {
    case currentWindow::Product:
        //product.update(window);
        break;
    
    case currentWindow::Factory:
        factory.update(window);
        break;
    }
}

void WorkCycle::draw() {
    // Clear the window
    window.clear(sf::Color(20, 20, 20));

    // Showing select options
    selectProductButton.draw(window);
    selectFactoryButton.draw(window);
    
    // Draw target
    switch (target) {
    case currentWindow::Product:
        product.draw(window);
        break;
    
    case currentWindow::Factory:
        factory.draw(window);
        break;
    }
    // Display things on screen
    window.display();
}

