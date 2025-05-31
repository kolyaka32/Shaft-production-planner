#include "processCycle.hpp"


ProcessCycle::ProcessCycle(Window& window)
: SubmenuCycle(window),
planner(window),
targetInputText(window, 280, 550, LanguagedText{"Target part production [prt/h]", "Целевой уровень производства [Дет/ч]"}),
targetInput(window, 550, 555, 80, planner.getTargetProduction())
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
    if (targetInput.click(pos)) {
        planner.setTargetProduction(targetInput.getNumber());
    }
}

void ProcessCycle::LUnClick(sf::Vector2i pos) {
    targetInput.unClick();
}

void ProcessCycle::RClick(sf::Vector2i pos) {
    // Pass
}

void ProcessCycle::keyDown(sf::Event::KeyPressed state) {
    // Check, if stop input - update values
    if (targetInput.keyPress(state)) {
        planner.setTargetProduction(targetInput.getNumber());
    }
}

void ProcessCycle::textInput(char32_t keyCode) {
    targetInput.inputText(keyCode);
}

void ProcessCycle::update() {
    targetInput.update(sf::Mouse::getPosition(window));
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
    planner.draw(window);
    targetInputText.draw(window);
    targetInput.draw(window);

    settings.draw(window);

    // Display things on screen
    window.display();
}
