#include "ProductCycle.hpp"


ProductCycle::ProductCycle(Window& window)
: SubmenuCycle(window),
partPicture(340, 200, 673, 210, "machines/shaftBlueprint.png"),
widthInput(window, 260, 260, 100, "120"),
heightInput(window, 680, 95, 60, "40"),
materialText(window, 850, 60, {"Material:", "Материал:"}),
materialSwitch(window, 750, 100, (LanguagedText[]){{"Steel", "Сталь"}, {"Alloys","Цветные сплавы"}, {"Heat-resistant steel","Жаропрочная сталь"}}) {}

void ProductCycle::LClick(sf::Vector2i pos) {
    // Checking global objects
    if (selectFactoryButton.isClicked(pos)) {
        App::startNext(Cycle::FactoryPlaner);
        stop();
        return;
    }
    if (settings.click(pos)) {
        stop();
        return;
    }

    // Current part
    // Check, if stop input - update values
    if (widthInput.click(pos)) {
        //factory.setWidth(widthBox.getNumber());
    }
    if (heightInput.click(pos)) {
        //factory.setHeight(heightBox.getNumber());
    }
    if (materialSwitch.click(pos)) {
        //pass
    }
}

void ProductCycle::LUnClick(sf::Vector2i pos) {
    widthInput.unClick();
    heightInput.unClick();
}

void ProductCycle::RClick(sf::Vector2i pos) {
    // Pass
}

void ProductCycle::keyDown(sf::Event::KeyPressed state) {
    widthInput.keyPress(state);
    heightInput.keyPress(state);
}

void ProductCycle::textInput(char32_t keyCode) {
    widthInput.inputText(keyCode);
    heightInput.inputText(keyCode);
}

void ProductCycle::update() {
    widthInput.update(sf::Mouse::getPosition(window));
    heightInput.update(sf::Mouse::getPosition(window));
}

void ProductCycle::draw() {
    // Draw global objects
    window.clear(sf::Color(20, 20, 20));
    selectProductButton.draw(window);
    selectFactoryButton.draw(window);
    settings.draw(window);

    // Draw main part
    partPicture.draw(window);
    widthInput.draw(window);
    heightInput.draw(window);
    materialText.draw(window);
    materialSwitch.draw(window);

    // Display things on screen
    window.display();
}
