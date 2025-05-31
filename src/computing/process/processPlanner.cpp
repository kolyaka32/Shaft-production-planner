#include "processPlanner.hpp"


ProcessPlanner::ProcessPlanner(Window& window)
: backGround({1200, 150}),
stepTexts {
    {window, getOffset(0), 90, LanguagedText{"Rough", "Черновая"}},
    {window, getOffset(1), 120, LanguagedText{"Thermal", "Термическая"}},
    {window, getOffset(2), 90, LanguagedText{"Main", "Получистовая"}},
    {window, getOffset(3), 120, LanguagedText{"Thermal", "Термическая"}},
    {window, getOffset(4), 90, LanguagedText{"Trimming", "Чистовая"}},
    {window, getOffset(5), 120, LanguagedText{"Thermal", "Термическая"}},
    {window, getOffset(6), 90, LanguagedText{"Finishing", "Отделочная"}},
    {window, getOffset(7), 120, LanguagedText{"Thermal", "Термическая"}},
},
timeDescription(window, 5, 150, LanguagedText{"Time [h]:", "Время [ч]:"}, GUI::Aligment::Left),
machinesDescription(window, 5, 180, LanguagedText{"Lathes:", "Станков:"}, GUI::Aligment::Left),
furnacesDescription(window, 5, 210, LanguagedText{"Furnaces:", "Печей:"}, GUI::Aligment::Left),
timeTexts {
    {window.font}, {window.font}, {window.font}, {window.font},
    {window.font}, {window.font}, {window.font}, {window.font},
},
countTexts {
    {window.font}, {window.font}, {window.font}, {window.font},
    {window.font}, {window.font}, {window.font}, {window.font},
},
summaryText(window, getOffset(8)+60, 90, LanguagedText{"Sumary:", "Суммарно:"}),
productionTimeText(window, getOffset(8)+60, 150, std::format("{:.1f}", getPartProductionTime())),
machineCountText(window, getOffset(8)+60, 180, std::to_string(getLatheCount())),
furnaceCountText(window, getOffset(8)+60, 210, std::to_string(getFurnaceCount()))
{
    // Setting background
    backGround.setPosition({0, 95});
    backGround.setFillColor(sf::Color{120, 120, 120});

    // Updating texts
    for (int i=startStep; i < endStep; ++i) {
        timeTexts[i*2].setString(std::format("{:.1f}", mechanicalStages[i].getTimePerOperation()));
        timeTexts[i*2].setOrigin(timeTexts[i*2].getGlobalBounds().size/2.0f);
        timeTexts[i*2].setPosition({getOffset(i*2), 165.0f});
        countTexts[i*2].setString(std::to_string(mechanicalStages[i].getNeedLathes()));
        countTexts[i*2].setOrigin(countTexts[i*2].getGlobalBounds().size/2.0f);
        countTexts[i*2].setPosition({getOffset(i*2), 195.0f});
        timeTexts[i*2+1].setString(std::format("{:.1f}", thermalStages[i].getTimePerOperation()));
        timeTexts[i*2+1].setOrigin(timeTexts[i*2+1].getGlobalBounds().size/2.0f);
        timeTexts[i*2+1].setPosition({getOffset(i*2+1), 165.0f});
        countTexts[i*2+1].setString(std::to_string(thermalStages[i].getNeedFurnaces()));
        countTexts[i*2+1].setOrigin(countTexts[i*2+1].getGlobalBounds().size/2.0f);
        countTexts[i*2+1].setPosition({getOffset(i*2+1), 225.0f});
    }
}

constexpr float ProcessPlanner::getOffset(int index) {
    return stepOffset*index+stepStartOffset;
}

void ProcessPlanner::setTargetProduction(float _target) {
    partProductionTarget = _target;
    update();
}

void ProcessPlanner::setTargetVolume(int _target) {
    partVolumeTarget = _target;
    update();
}

std::string ProcessPlanner::getTargetProduction() {
    return std::format("{:.1f}", partProductionTarget);
}

std::string ProcessPlanner::getTargetVolume() {
    return std::to_string(partVolumeTarget);
}

void ProcessPlanner::update() {
    // Update process parameters
    recalculate();
    // Updating texts
    for (int i=startStep; i < endStep; ++i) {
        timeTexts[i*2].setString(std::format("{:.1f}", mechanicalStages[i].getTimePerOperation()));
        timeTexts[i*2].setOrigin(timeTexts[i*2].getGlobalBounds().size/2.0f);
        countTexts[i*2].setString(std::to_string(mechanicalStages[i].getNeedLathes()));
        countTexts[i*2].setOrigin(countTexts[i*2].getGlobalBounds().size/2.0f);
        timeTexts[i*2+1].setString(std::format("{:.1f}", thermalStages[i].getTimePerOperation()));
        timeTexts[i*2+1].setOrigin(timeTexts[i*2+1].getGlobalBounds().size/2.0f);
        countTexts[i*2+1].setString(std::to_string(thermalStages[i].getNeedFurnaces()));
        countTexts[i*2+1].setOrigin(countTexts[i*2+1].getGlobalBounds().size/2.0f);
    }
    productionTimeText.setText(std::format("{:.1f}", getPartProductionTime()));
    machineCountText.setText(std::to_string(getLatheCount()));
    furnaceCountText.setText(std::to_string(getFurnaceCount()));
}

void ProcessPlanner::draw(Window& window) {
    // Background
    window.draw(backGround);

    // Table
    timeDescription.draw(window);
    machinesDescription.draw(window);
    furnacesDescription.draw(window);
    for (int i=startStep*2; i < endStep*2; ++i) {
        stepTexts[i].draw(window);
        window.draw(timeTexts[i]);
        window.draw(countTexts[i]);
    }
    
    // Summary
    summaryText.draw(window);
    productionTimeText.draw(window);
    machineCountText.draw(window);
    furnaceCountText.draw(window);
}
