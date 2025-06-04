#include "factoryCycle.hpp"


FactoryCycle::FactoryCycle(Window& window)
: SubmenuCycle(window),
factory(window, {250, 200}),
widthText(window, 80, 100, LanguagedText{"Width", "Ширина"}),
widthBox(window, 40, 140, 80, Factory::getWidth()),
heightText(window, 200, 100, LanguagedText{"Height", "Высота"}),
heightBox(window, 160, 140, 80, Factory::getHeight()),
cellTypeSwitch(window, 5, 200, (LanguagedText[]){{"None", "Ничего"}, {"Path tile", "Клетка пути"},
    {"Lathe 1", "Станок 1"}, {"Furnace 1", "Печь 1"}, {"Warehouse", "Склад"}}),
optimizeButton(window, 5, 400, {"Try optimize", "Оптимизировать"}, GUI::Aligment::Left),
updatePathButton(window, 5, 450, {"Update pathes", "Обновить пути"}, GUI::Aligment::Left),
cursorCell() {}

void FactoryCycle::LClick(sf::Vector2i pos) {
    // Checking global objects
    if (selectProductButton.isClicked(pos)) {
        App::startNext(Cycle::ProductPlanner);
        stop();
        return;
    }
    if (selectProcessButton.isClicked(pos)) {
        App::startNext(Cycle::ProcessPlanner);
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
        selectObject = true;
        switch (cellTypeSwitch.getValue()) {
        case 0:
            selectObject = false;
            return;
        
        case 1:
            cursorCell.setType(CellType::UnspecifiedWay);
            break;

        case 2:
            cursorCell.setType(CellType::Lathe_1);
            break;

        case 3:
            cursorCell.setType(CellType::Furnace_1);
            break;

        case 4:
            cursorCell.setType(CellType::Warehouse);
            break;
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
    // Check on trying to optimise field
    if (optimizeButton.isClicked(pos)) {
        factory.tryOptimize();
    }
    if (updatePathButton.isClicked(pos)) {
        factory.updateWays();
    }
    // Check, if stop input - update grid scales
    if (widthBox.click(pos)) {
        int number = widthBox.getNumber();
        // Check on getting over border
        if (number > 18) {
            number = 18;
        }
        factory.setWidth(number);
    }
    if (heightBox.click(pos)) {
        int number = heightBox.getNumber();
        // Check on getting over border
        if (number > 10) {
            number = 10;
        }
        factory.setHeight(number);
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

void FactoryCycle::keyDown(sf::Event::KeyPressed state) {
    if (widthBox.keyPress(state)) {
        int number = widthBox.getNumber();
        // Check on getting over border
        if (number > 18) {
            number = 18;
            widthBox.setString("18");
        }
        factory.setWidth(number);
    }
    if (heightBox.keyPress(state)) {
        int number = heightBox.getNumber();
        // Check on getting over border
        if (number > 10) {
            number = 10;
            heightBox.setString("10");
        }
        factory.setHeight(number);
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
    selectProcessButton.draw(window);
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

    settings.draw(window);

    // Draw selected object
    if (selectObject) {
        cursorCell.draw(window, sf::Mouse::getPosition(window));
    }

    optimizeButton.draw(window);
    updatePathButton.draw(window);

    // Display things on screen
    window.display();
}
