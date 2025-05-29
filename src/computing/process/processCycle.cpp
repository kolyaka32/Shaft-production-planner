#include "processCycle.hpp"


ProcessCycle::ProcessCycle(Window& window)
: SubmenuCycle(window),
planner()
{}

void ProcessCycle::LClick(sf::Vector2i pos) {
    // Checking global objects
    if (selectFactoryButton.isClicked(pos)) {
        App::startNext(Cycle::FactoryPlaner);
        stop();
        return;
    }
    if (selectProductButton.isClicked(pos)) {
        App::startNext(Cycle::ProductPlanner);
        stop();
        return;
    }
    if (settings.click(pos)) {
        stop();
        return;
    }
    if (saveButton.isClicked(pos)) {
        save();
        saveInfo.reset();
        return;
    }
    if (loadButton.isClicked(pos)) {
        load();
        // Restarting cycle
        stop();
        return;
    }

    // Check, if stop input - update values
    /*if (partWidthInput.click(pos)) {
        process.setTargetLength(partWidthInput.getNumber());
    }*/
}

void ProcessCycle::LUnClick(sf::Vector2i pos) {
    //partWidthInput.unClick();
}

void ProcessCycle::RClick(sf::Vector2i pos) {
    // Pass
}

void ProcessCycle::keyDown(sf::Event::KeyPressed state) {
    // Check, if stop input - update values
    /*if (partWidthInput.keyPress(state)) {
        process.setTargetLength(partWidthInput.getNumber());
    }*/
}

void ProcessCycle::textInput(char32_t keyCode) {
    //partWidthInput.inputText(keyCode);
}

void ProcessCycle::update() {
    // partWidthInput.update(sf::Mouse::getPosition(window));
}

void ProcessCycle::draw() {
    // Draw global objects
    window.clear(sf::Color(20, 20, 20));
    selectProductButton.draw(window);
    selectProcessButton.draw(window);
    selectFactoryButton.draw(window);
    saveButton.draw(window);
    loadButton.draw(window);
    saveInfo.draw(window);

    // Draw main part


    settings.draw(window);

    // Display things on screen
    window.display();
}
