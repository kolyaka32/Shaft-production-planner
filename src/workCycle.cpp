#include "workCycle.hpp"

#include <iostream>

WorkCycle::WorkCycle(Window& window)
: CycleTemplate(window),
button1(window, 100, 200, 80, 40, {"Type1", "abc"}),
button2(window, 100, 250, 80, 40, {"Type2", "lan2"}),
button3(window, 100, 300, 80, 40, {"Type3", "lan2"}),
button4(window, 100, 350, 80, 40, {"None", "lan2"}),
typeBox(window, 300, 500, 400, "ABC"),
factory(10, 5, {300, 200}),
cursorMachine() {

}

WorkCycle::~WorkCycle() {

}

void WorkCycle::keyDown(sf::Event::KeyPressed state) {
    typeBox.keyPress(state);
}

void WorkCycle::mouseClick(sf::Vector2i pos) {
    // Selecting type for setting it
    if (button1.isClicked(pos)) {
        selectObject = true;
        cursorMachine.setType(Cell::Type::Machine_1);
    } else if (button2.isClicked(pos)) {
        selectObject = true;
        cursorMachine.setType(Cell::Type::Machine_2);
    } else if (button3.isClicked(pos)) {
        selectObject = true;
        cursorMachine.setType(Cell::Type::Furnace_1);
    } else if (button4.isClicked(pos)) {
        selectObject = false;
    } else if (factory.isSelected(pos) && selectObject) {
        // Setting object in grid
        factory.set(cursorMachine.getType(), pos);
    } else {
        selectObject = false;
    }
    //typeBox.click(pos);
}

void WorkCycle::mouseUnClick(sf::Vector2i pos) {
    //typeBox.unClick();
}

void WorkCycle::textInput(char32_t keyCode) {
    //typeBox.inputText(keyCode);
}

void WorkCycle::update() {
    //typeBox.update(sf::Mouse::getPosition(window));
}

void WorkCycle::draw() {
    // Clear the window
    window.clear(sf::Color(20, 20, 20));

    factory.draw(window);

    button1.draw(window);
    button2.draw(window);
    button3.draw(window);
    button4.draw(window);

    // Draw selected object
    if (selectObject) {
        cursorMachine.draw(window, sf::Mouse::getPosition(window));
    }

    //typeBox.draw(window);

    // Display things on screen
    window.display();
}
