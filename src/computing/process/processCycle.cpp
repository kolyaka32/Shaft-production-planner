#include "processCycle.hpp"


ProcessCycle::ProcessCycle(Window& window)
: SubmenuCycle(window),
planner(window),
targetProductionInputText(window, 10, 350, LanguagedText{"Target part production [prt/h]", "Целевой уровень производства [Дет/ч]"}, GUI::Aligment::Left),
targetProductionInput(window, 550, 355, 80, planner.getTargetProduction()),
targetVolumeInputText(window, 10, 390, LanguagedText{"Batch size", "Объём партии"}, GUI::Aligment::Left),
targetVolumeInput(window, 550, 395, 80, planner.getTargetVolume()),
batchTimeText(window, 10, 430, getBatchTimeText(), GUI::Aligment::Left),
batchCostText(window, 10, 470, getBatchCostText(), GUI::Aligment::Left),
avaragePartCost(window, 10, 510, getAvaragePartText(), GUI::Aligment::Left)
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
        batchTimeText.setText(getBatchTimeText());
        batchCostText.setText(getBatchCostText());
        avaragePartCost.setText(getAvaragePartText());
    }
    if (targetVolumeInput.click(pos)) {
        planner.setTargetVolume(targetVolumeInput.getNumber());
        batchTimeText.setText(getBatchTimeText());
        batchCostText.setText(getBatchCostText());
        avaragePartCost.setText(getAvaragePartText());
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
        batchTimeText.setText(getBatchTimeText());
        batchCostText.setText(getBatchCostText());
        avaragePartCost.setText(getAvaragePartText());
    }
    if (targetVolumeInput.keyPress(state)) {
        planner.setTargetVolume(targetVolumeInput.getNumber());
        batchTimeText.setText(getBatchTimeText());
        batchCostText.setText(getBatchCostText());
        avaragePartCost.setText(getAvaragePartText());
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
    batchTimeText.draw(window);
    batchCostText.draw(window);
    avaragePartCost.draw(window);

    settings.draw(window);

    // Display things on screen
    window.display();
}

std::string ProcessCycle::getBatchTimeText() {
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        return std::format("Time per whole batch [h]: {:.1f}", planner.getVolumeProductionTime());

    case Language::Russian:
        return std::format("Время выполнения партии [ч]: {:.1f}", planner.getVolumeProductionTime());
    }
    return "";
}

std::string ProcessCycle::getBatchCostText() {
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        return std::format("Cost of batch [rub]: {:.0f}", planner.getBatchCost());

    case Language::Russian:
        return std::format("Стоимость партии [руб]: {:.0f}", planner.getBatchCost());
    }
    return "";
}

std::string ProcessCycle::getAvaragePartText() {
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        return std::format("Cost per one part [rub/prt]: {:.1f}", planner.getAvaragePartCost());

    case Language::Russian:
        return std::format("Себестоимость детали [руб/дет]: {:.1f}", planner.getAvaragePartCost());
    }
    return "";
}
