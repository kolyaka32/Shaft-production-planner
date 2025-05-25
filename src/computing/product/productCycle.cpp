#include "ProductCycle.hpp"


ProductCycle::ProductCycle(Window& window)
: SubmenuCycle(window),
process(window),
partPicture(0, 60, "machines/shaftBlueprint.png"),
partWidthInput(window, 250, 245, 100, process.getTargetLength()),
partHeightInput(window, 655, 115, 70, process.getTargetDiameter()),
partRoughnessInput(window, 655, 65, 70, process.getTargetRoughness()),
blankPicture(0, 300, "machines/blankBlueprint.png"),
blankWidthInput(window, 250, 445, 100, process.getBlankLength()),
blankHeightInput(window, 620, 350, 70, process.getBlankDiameter()),
blankRoughnessInput(window, 620, 305, 70, process.getBlankRoughness()),
materialText(window, 880, 60, {"Material:", "Материал:"}),
materialSwitch(window, 740, 100, (LanguagedText[]){
    {"Steel", "Сталь"},
    {"Alloys", "Цветные сплавы"},
    {"Heat-resistant steel", "Жаропрочная сталь"}})
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

    // Check, if stop input - update values
    if (partWidthInput.click(pos)) {
        process.setTargetLength(partWidthInput.getNumber());
    }
    if (partHeightInput.click(pos)) {
        process.setTargetDiameter(partHeightInput.getNumber());
    }
    if (partRoughnessInput.click(pos)) {
        process.setTargetRoughness(partRoughnessInput.getNumber());
    }
    if (blankWidthInput.click(pos)) {
        process.setBlankLength(blankWidthInput.getNumber());
    }
    if (blankHeightInput.click(pos)) {
        process.setBlankDiameter(blankHeightInput.getNumber());;
    }
    if (blankRoughnessInput.click(pos)) {
        process.setBlankRoughness(blankRoughnessInput.getNumber());
    }
    if (materialSwitch.click(pos)) {
        process.setMaterial(materialSwitch.getValue());
    }
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

    process.draw(window);

    settings.draw(window);

    // Display things on screen
    window.display();
}
