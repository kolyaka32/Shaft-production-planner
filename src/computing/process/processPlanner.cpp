#include "processPlanner.hpp"


ProcessPlanner::ProcessPlanner(Window& window)
: backGround({1200, 165}),
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
singleTimeDescription(window, 5, 150, LanguagedText{"Per part:", "На деталь:"}, GUI::Aligment::Left),
machinesDescription(window, 5, 180, LanguagedText{"Lathes:", "Станков:"}, GUI::Aligment::Left),
furnacesDescription(window, 5, 210, LanguagedText{"Furnaces:", "Печей:"}, GUI::Aligment::Left),
singleTimeTexts {
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
        // Mechanical step
        singleTimeTexts[i*2].setPosition({getOffset(i*2), 165.0f});
        countTexts[i*2].setPosition({getOffset(i*2), 195.0f});
        // Thermal step
        singleTimeTexts[i*2+1].setPosition({getOffset(i*2+1), 165.0f});
        countTexts[i*2+1].setPosition({getOffset(i*2+1), 225.0f});
    }
    // Update all texts
    update();
}

constexpr float ProcessPlanner::getOffset(int index) {
    return stepOffset*index+stepStartOffset;
}

void ProcessPlanner::setTargetProduction(float _target) {
    partProductionTarget = _target;
    // Update process parameters
    recalculate();
    // Updating texts
    update();
}

void ProcessPlanner::setTargetVolume(int _target) {
    targetBatchVolume = _target;
    // Update process parameters
    recalculate();
    // Updating texts
    update();
}

std::string ProcessPlanner::getTargetProduction() {
    return std::format("{:.1f}", partProductionTarget);
}

std::string ProcessPlanner::getTargetVolume() {
    return std::to_string(targetBatchVolume);
}

void ProcessPlanner::update() {
    // Updating texts
    for (int i=startStep; i < endStep; ++i) {
        // Mechanical part
        singleTimeTexts[i*2].setString(std::format("{:.1f}", mechanicalStages[i].getTimePerOperation()));
        singleTimeTexts[i*2].setOrigin(singleTimeTexts[i*2].getGlobalBounds().size/2.0f);
        countTexts[i*2].setString(std::to_string(mechanicalStages[i].getReqieredQuantity()));
        countTexts[i*2].setOrigin(countTexts[i*2].getGlobalBounds().size/2.0f);
        // Thermal part
        singleTimeTexts[i*2+1].setString(std::format("{:.1f}", thermalStages[i].getTimePerOperation()));
        singleTimeTexts[i*2+1].setOrigin(singleTimeTexts[i*2+1].getGlobalBounds().size/2.0f);
        countTexts[i*2+1].setString(std::to_string(thermalStages[i].getReqieredQuantity()));
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
    singleTimeDescription.draw(window);
    machinesDescription.draw(window);
    furnacesDescription.draw(window);
    for (int i=startStep*2; i < endStep*2; ++i) {
        stepTexts[i].draw(window);
        window.draw(singleTimeTexts[i]);
        window.draw(countTexts[i]);
    }
    
    // Summary
    summaryText.draw(window);
    productionTimeText.draw(window);
    machineCountText.draw(window);
    furnaceCountText.draw(window);
}
