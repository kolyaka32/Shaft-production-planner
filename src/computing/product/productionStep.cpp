#include "productionStep.hpp"
#include <cmath>

ProductionStep::ProductionStep(Window& window, float X, float Y, LanguagedText _text)
: stepText(window, X+35, Y-40, _text),
arrowTexture(resourcesDir() / "GUI/arrow.png"),
arrowSprite(arrowTexture) {
    arrowSprite.setPosition({X+5, Y});
}

void ProductionStep::draw(Window& window) {
    window.draw(arrowSprite);
    stepText.draw(window);
}
