#pragma once

#include "../global/submenuCycle.hpp"
#include "../process.hpp"


// 
class ProcessPlanner : public Process {
private:
    // Grphical constants and macroses
    const float stepOffset = 110, stepStartOffset = 170;
    constexpr float getOffset(int index);

    // Graphical part
    sf::RectangleShape backGround;
    GUI::Text singleTimeDescription;
    GUI::Text machinesDescription, furnacesDescription;
    GUI::Text stepTexts[8];
    GUI::Text summaryText;
    sf::Text singleTimeTexts[8];
    sf::Text countTexts[8];
    GUI::Text productionTimeText, machineCountText, furnaceCountText;

protected:
    void update();

public:
    ProcessPlanner(Window& window);
    void setTargetProduction(float target);
    void setTargetVolume(int target);
    std::string getTargetProduction();
    std::string getTargetVolume();
    void draw(Window& window);
};
