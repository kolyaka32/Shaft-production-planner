#include "productSubWindow.hpp"


ProductSubWindow::ProductSubWindow(Window& window)
: partPicture(340, 200, 673, 210, "machines/shaftBlueprint.png"),
widthInput(window, 260, 260, 100, "120"),
heightInput(window, 680, 95, 60, "40"),
materialSwitch(window, 700, 100, {
    (LanguagedText){{"Steel", "Сталь"}},
    (LanguagedText){{"Alloys","Цветные сплавы"}},
    (LanguagedText){{"Heat-resistant steel","Жаропрочная сталь"}}}) {}

void ProductSubWindow::LClick(Window& window, sf::Vector2i pos) {
    // Check, if stop input - update values
    if (widthInput.click(pos)) {
        //factory.setWidth(widthBox.getNumber());
    }
    if (heightInput.click(pos)) {
        //factory.setHeight(heightBox.getNumber());
    }
}

void ProductSubWindow::LUnClick(sf::Vector2i pos) {
    widthInput.unClick();
    heightInput.unClick();
}

void ProductSubWindow::RClick(sf::Vector2i pos) {
    // Pass
}

void ProductSubWindow::keyDown(sf::Event::KeyPressed state) {
    widthInput.keyPress(state);
    heightInput.keyPress(state);
}

void ProductSubWindow::textInput(char32_t keyCode) {
    widthInput.inputText(keyCode);
    heightInput.inputText(keyCode);
}

void ProductSubWindow::update(Window& window) {
    widthInput.update(sf::Mouse::getPosition(window));
    heightInput.update(sf::Mouse::getPosition(window));
}

void ProductSubWindow::draw(Window& window) {
    partPicture.draw(window);
    widthInput.draw(window);
    heightInput.draw(window);
}
