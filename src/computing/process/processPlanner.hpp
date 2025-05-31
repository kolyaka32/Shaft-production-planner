#pragma once

#include "../global/submenuCycle.hpp"
#include "../process.hpp"


// 
class ProcessPlanner : public Process {
private:
    // Grphical constants and macroses
    const float stepOffset = 110, stepStartOffset = 160;
    constexpr float getOffset(int index);

    // Graphical part
    GUI::Text stepTexts[8];
    GUI::Text timeDescription, machinesDescription, furnacesDescription;
    sf::Text timeTexts[8];
    sf::Text countTexts[8];
    GUI::Text summaryText;
    GUI::Text productionTimeText, machineCountText, furnaceCountText;

protected:
    void update();

public:
    ProcessPlanner(Window& window);
    void setTargetProduction(float target);
    std::string getTargetProduction();
    void draw(Window& window);
};
