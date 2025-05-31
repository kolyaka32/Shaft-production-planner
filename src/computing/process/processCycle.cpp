#include "processCycle.hpp"


ProcessCycle::ProcessCycle(Window& window)
: SubmenuCycle(window),
planner(window),
targetProductionInputText(window, 10, 350, LanguagedText{"Target part production [prt/h]", "Целевой уровень производства [Дет/ч]"}, GUI::Aligment::Left),
targetProductionInput(window, 550, 355, 80, planner.getTargetProduction()),
targetVolumeInputText(window, 10, 390, LanguagedText{"Batch size", "Объём партии"}, GUI::Aligment::Left),
targetVolumeInput(window, 550, 395, 80, planner.getTargetVolume()),
batchProductionTimeText(window, 10, 430, getBatchText(), GUI::Aligment::Left)
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
    if (targetProductionInput.click(pos)) {
        planner.setTargetProduction(targetProductionInput.getNumber());
        batchProductionTimeText.setText(getBatchText());
    }
    if (targetVolumeInput.click(pos)) {
        planner.setTargetVolume(targetVolumeInput.getNumber());
        batchProductionTimeText.setText(getBatchText());
    }
}

void ProcessCycle::LUnClick(sf::Vector2i pos) {
    targetProductionInput.unClick();
    targetVolumeInput.unClick();
}

void ProcessCycle::RClick(sf::Vector2i pos) {
    // Pass
}

void ProcessCycle::keyDown(sf::Event::KeyPressed state) {
    // Check, if stop input - update values
    if (targetProductionInput.keyPress(state)) {
        planner.setTargetProduction(targetProductionInput.getNumber());
        batchProductionTimeText.setText(getBatchText());
    }
    if (targetVolumeInput.keyPress(state)) {
        planner.setTargetVolume(targetVolumeInput.getNumber());
        batchProductionTimeText.setText(getBatchText());
    }
}

void ProcessCycle::textInput(char32_t keyCode) {
    targetProductionInput.inputText(keyCode);
    targetVolumeInput.inputText(keyCode);
}

void ProcessCycle::update() {
    targetProductionInput.update(sf::Mouse::getPosition(window));
    targetVolumeInput.update(sf::Mouse::getPosition(window));
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
    targetProductionInputText.draw(window);
    targetProductionInput.draw(window);
    targetVolumeInputText.draw(window);
    targetVolumeInput.draw(window);
    batchProductionTimeText.draw(window);

    settings.draw(window);

    // Display things on screen
    window.display();
}

std::string ProcessCycle::getBatchText() {
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        return std::format("Time per whole batch [h]: {:.0f}", planner.getVolumeProductionTime());

    case Language::Russian:
        return std::format("Время выполнения партии [ч]: {:.0f}", planner.getVolumeProductionTime());
    }
    return "";
}
