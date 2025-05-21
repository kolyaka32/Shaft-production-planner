#include "ProductCycle.hpp"


ProductCycle::ProductCycle(Window& window)
: SubmenuCycle(window),
partPicture(0, 60, "machines/shaftBlueprint.png"),
partWidthInput(window, 250, 245, 100, "120"),
partHeightInput(window, 655, 115, 60, "80"),
partRoughnessInput(window, 655, 65, 60, "40"),
blankPicture(0, 300, "machines/blankBlueprint.png"),
blankWidthInput(window, 250, 445, 100, "120"),
blankHeightInput(window, 620, 350, 60, "80"),
blankRoughnessInput(window, 620, 310, 60, "40"),
materialText(window, 850, 60, {"Material:", "Материал:"}),
materialSwitch(window, 720, 100, (LanguagedText[]){{"Steel", "Сталь"}, {"Alloys","Цветные сплавы"}, {"Heat-resistant steel","Жаропрочная сталь"}})
{}

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
    /*if (widthInput.click(pos)) {
        //factory.setWidth(widthBox.getNumber());
    }
    if (heightInput.click(pos)) {
        //factory.setHeight(heightBox.getNumber());
    }
    if (materialSwitch.click(pos)) {
        //pass
    }
    if (roughnessInput.click(pos)) {
        //pass
    }*/
}

void ProductCycle::LUnClick(sf::Vector2i pos) {
    partWidthInput.unClick();
    partHeightInput.unClick();
    partRoughnessInput.unClick();
    blankWidthInput.unClick();
    blankHeightInput.unClick();
    blankRoughnessInput.unClick();
}

void ProductCycle::RClick(sf::Vector2i pos) {
    // Pass
}

void ProductCycle::keyDown(sf::Event::KeyPressed state) {
    partWidthInput.keyPress(state);
    partHeightInput.keyPress(state);
    partRoughnessInput.keyPress(state);
    blankWidthInput.keyPress(state);
    blankHeightInput.keyPress(state);
    blankRoughnessInput.keyPress(state);
}

void ProductCycle::textInput(char32_t keyCode) {
    partWidthInput.inputText(keyCode);
    partHeightInput.inputText(keyCode);
    partRoughnessInput.inputText(keyCode);
    blankWidthInput.inputText(keyCode);
    blankHeightInput.inputText(keyCode);
    blankRoughnessInput.inputText(keyCode);
}

void ProductCycle::update() {
    partWidthInput.update(sf::Mouse::getPosition(window));
    partHeightInput.update(sf::Mouse::getPosition(window));
    partRoughnessInput.update(sf::Mouse::getPosition(window));
    blankWidthInput.update(sf::Mouse::getPosition(window));
    blankHeightInput.update(sf::Mouse::getPosition(window));
    blankRoughnessInput.update(sf::Mouse::getPosition(window));
}

void ProductCycle::draw() {
    // Draw global objects
    window.clear(sf::Color(20, 20, 20));
    selectProductButton.draw(window);
    selectFactoryButton.draw(window);

    // Draw main part
    partPicture.draw(window);
    partWidthInput.draw(window);
    partHeightInput.draw(window);
    partRoughnessInput.draw(window);
    blankPicture.draw(window);
    blankWidthInput.draw(window);
    blankHeightInput.draw(window);
    blankRoughnessInput.draw(window);
    materialText.draw(window);
    materialSwitch.draw(window);

    settings.draw(window);

    // Display things on screen
    window.display();
}
