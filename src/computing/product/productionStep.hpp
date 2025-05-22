#include "../../app/cycleTemplate.hpp"


// Class showing one process step of part production
class ProductionStep {
private:
    sf::RectangleShape background;
    GUI::Text stepText;
    bool visability = false;
    float roughness;

public:
    ProductionStep(Window& window, float X, float Y, float checkRoughness, LanguagedText text);
    void setNew(float roughness);
    void draw(Window& window);
};
