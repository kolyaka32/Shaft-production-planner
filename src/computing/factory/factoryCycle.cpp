#include "factoryCycle.hpp"


FactoryCycle::FactoryCycle(Window& window)
: SubmenuCycle(window),
widthText(window, 80, 100, {"Width", "Ширина"}),
widthBox(window, 40, 140, 80, Factory::getWidth()),
heightText(window, 200, 100, {"Height", "Высота"}),
heightBox(window, 160, 140, 80, Factory::getHeight()),
cellTypeSwitch(window, 20, 200, (LanguagedText[]){{"None", "Ничего"},{"Path tile", "Клетка пути"},
    {"Cargo", "Склад"},{"Machine 1", "Станок 1"},{"Machine 2", "Станок 2"},{"Furnace 1", "Печь 1"}}),
updateLinkageButton(window, 20, 450, 150, 40, {"Update", "Обновить"}),
factory({200, 200}),
cursorCell() {}

void FactoryCycle::keyDown(sf::Event::KeyPressed state) {
    widthBox.keyPress(state);
    heightBox.keyPress(state);
}

void FactoryCycle::LClick(sf::Vector2i pos) {
    // Checking global objects
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
        // Restarting cycle to apply changes
        stop();
        return;
    }

    // Checking, if select new type of cell
    if (cellTypeSwitch.click(pos)) {
        if (cellTypeSwitch.getValue() == 0) {
            selectObject = false;
        } else {
            selectObject = true;
            cursorCell.setType((CellType)(cellTypeSwitch.getValue()+1));
        }
        return;
    }
    if (factory.isSelected(pos)) {
        // Setting object in grid
        if (selectObject) {
            factory.set(cursorCell.getType(), pos);
        } else {
            factory.reset(pos);
        }
        return;
    }
    // Resetting curent setting object
    selectObject = false;
    //cellTypeSwitch.set(0);
    if (updateLinkageButton.isClicked(pos)) {
        // Updating grid connection warning
        factory.checkConnections();
        return;
    }
    // Check, if stop input - update grid scales
    if (widthBox.click(pos)) {
        factory.setWidth(widthBox.getNumber());
    }
    if (heightBox.click(pos)) {
        factory.setHeight(heightBox.getNumber());
    }
}

void FactoryCycle::LUnClick(sf::Vector2i pos) {
    widthBox.unClick();
    heightBox.unClick();
}

void FactoryCycle::RClick(sf::Vector2i pos) {
    if (selectObject) {
        selectObject = false;
        cellTypeSwitch.set(0);
    } else if (factory.isSelected(pos)) {
        // Setting object in grid
        factory.remove(pos);
    }
}

void FactoryCycle::textInput(char32_t keyCode) {
    widthBox.inputText(keyCode);
    heightBox.inputText(keyCode);
}

void FactoryCycle::update() {
    widthBox.update(sf::Mouse::getPosition(window));
    heightBox.update(sf::Mouse::getPosition(window));
}

void FactoryCycle::draw() {
    // Draw global objects
    window.clear(sf::Color(20, 20, 20));
    selectProductButton.draw(window);
    selectFactoryButton.draw(window);
    saveButton.draw(window);
    loadButton.draw(window);
    saveInfo.draw(window);

    // Draw input objects
    widthBox.draw(window);
    widthText.draw(window);
    heightBox.draw(window);
    heightText.draw(window);

    cellTypeSwitch.draw(window);

    // Draw grid
    factory.draw(window);

    // Draw global options
    updateLinkageButton.draw(window);

    settings.draw(window);

    // Draw selected object
    if (selectObject) {
        cursorCell.draw(window, sf::Mouse::getPosition(window));
    }

    // Display things on screen
    window.display();
}
