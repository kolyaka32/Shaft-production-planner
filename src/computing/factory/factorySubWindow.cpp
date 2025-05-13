#include "factorySubWindow.hpp"


FactorySubWindow::FactorySubWindow(Window& window)
: widthText(window, 80, 100, {"Width", "Ширина"}),
widthBox(window, 40, 140, 80, "10"),
heightText(window, 200, 100, {"Height", "Высота"}),
heightBox(window, 160, 140, 80, "5"),
cellTypeButtons {
    {window, 20, 200, 150, 40, {"Machine 1", "Станок 1"}},
    {window, 20, 250, 150, 40, {"Machine 2", "Станок 2"}},
    {window, 20, 300, 150, 40, {"Furnace 1", "Печь 1"}},
    {window, 20, 350, 150, 40, {"Path tile", "Клетка пути"}},
    {window, 20, 400, 150, 40, {"None", "Ничего"}},
},
updateLinkageButton(window, 20, 450, 150, 40, {"Update", "Обновить"}),
factory(10, 5, {200, 200}),
languageButtons {
    {920, 50, 120, 80, "GUI/Flag_ENG.png"},
    {920, 150, 120, 80, "GUI/Flag_RUS.png"},
},
saveButton(window, 20, 550, 150, 40, {"Save", "Сохранить"}),
loadButton(window, 20, 600, 150, 40, {"Load", "Загрузить"}),
saveInfo(window, 100, 500, {"Saved", "Сохранено"}),
cursorCell() {}

void FactorySubWindow::keyDown(sf::Event::KeyPressed state) {
    widthBox.keyPress(state);
    heightBox.keyPress(state);
}

void FactorySubWindow::LClick(Window& window, sf::Vector2i pos) {
    // Selecting type for setting it
    if (cellTypeButtons[0].isClicked(pos)) {
        selectObject = true;
        cursorCell.setType(CellType::Machine_1);
    } else if (cellTypeButtons[1].isClicked(pos)) {
        selectObject = true;
        cursorCell.setType(CellType::Machine_2);
    } else if (cellTypeButtons[2].isClicked(pos)) {
        selectObject = true;
        cursorCell.setType(CellType::Furnace_1);
    } else if (cellTypeButtons[3].isClicked(pos)) {
        selectObject = true;
        cursorCell.setType(CellType::Way);
    } else if (cellTypeButtons[4].isClicked(pos)) {
        selectObject = false;
    } else if (factory.isSelected(pos)) {
        // Setting object in grid
        if (selectObject) {
            factory.set(cursorCell.getType(), pos);
        } else {
            factory.reset(pos);
        }
    } else {
        selectObject = false;
        if (updateLinkageButton.isClicked(pos)) {
            // Updating grid connection warning
            factory.checkConnections();
        } else if (saveButton.isClicked(pos)) {
            factory.saveGrid("grid.cfg");
            // Showing message of sucsesfull saving
            saveInfo.reset();
        } else if (loadButton.isClicked(pos)) {
            factory.loadGrid("grid.cfg");
        } else if (languageButtons[0].isClicked(pos)) {
            if (window.language != (unsigned)Language::English) {
                window.language = (unsigned)Language::English;
                // Updating all objects
                updateLocation(window);
            }
        } else if (languageButtons[1].isClicked(pos)) {
            if (window.language != (unsigned)Language::Russian) {
                window.language = (unsigned)Language::Russian;
                // Updating all objects
                updateLocation(window);
            }
        } else {
            // Check, if stop input - update grid scales
            if (widthBox.click(pos)) {
                factory.setWidth(widthBox.getNumber());
            }
            if (heightBox.click(pos)) {
                factory.setHeight(heightBox.getNumber());
            }
        }
    } 
}

void FactorySubWindow::LUnClick(sf::Vector2i pos) {
    widthBox.unClick();
    heightBox.unClick();
}

void FactorySubWindow::RClick(sf::Vector2i pos) {
    if (selectObject) {
        selectObject = false;
    } else if (factory.isSelected(pos)) {
        // Setting object in grid
        factory.remove(pos);
    }
}

void FactorySubWindow::textInput(char32_t keyCode) {
    widthBox.inputText(keyCode);
    heightBox.inputText(keyCode);
}

void FactorySubWindow::update(Window& window) {
    widthBox.update(sf::Mouse::getPosition(window));
    heightBox.update(sf::Mouse::getPosition(window));
}

void FactorySubWindow::draw(Window& window) {
    // Draw input objects
    widthBox.draw(window);
    widthText.draw(window);
    heightBox.draw(window);
    heightText.draw(window);

    for (int i=0; i < 5; ++i) {
        cellTypeButtons[i].draw(window);
    }

    // Draw grid
    factory.draw(window);

    // Draw global options
    updateLinkageButton.draw(window);
    saveButton.draw(window);
    loadButton.draw(window);
    saveInfo.draw(window);
    languageButtons[0].draw(window);
    languageButtons[1].draw(window);

    // Draw selected object
    if (selectObject) {
        cursorCell.draw(window, sf::Mouse::getPosition(window));
    }
}

void FactorySubWindow::updateLocation(Window& window) {
    widthText.update(window);
    heightText.update(window);
    for (int i=0; i < 5; ++i) {
        cellTypeButtons[i].update(window);
    }
    saveButton.update(window);
    loadButton.update(window);
    saveInfo.update(window);
}
