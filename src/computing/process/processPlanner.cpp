#include "processPlanner.hpp"


ProcessPlanner::ProcessPlanner(Window& window)
: stepTexts {
    {window, getOffset(0)+20, 90, LanguagedText{"Rough", "Черновая"}},
    {window, getOffset(1)+20, 120, LanguagedText{"Thermal", "Термическая"}},
    {window, getOffset(2)+20, 90, LanguagedText{"Main", "Получистовая"}},
    {window, getOffset(3)+20, 120, LanguagedText{"Thermal", "Термическая"}},
    {window, getOffset(4)+20, 90, LanguagedText{"Trimming", "Чистовая"}},
    {window, getOffset(5)+20, 120, LanguagedText{"Thermal", "Термическая"}},
    {window, getOffset(6)+20, 90, LanguagedText{"Finishing", "Отделочная"}},
    {window, getOffset(7)+20, 120, LanguagedText{"Thermal", "Термическая"}},
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
productionTimeText(window, getOffset(8)+60, 150, std::format("{:.1f}", getProductionTime())),
machineCountText(window, getOffset(8)+60, 180, std::to_string(getLatheCount())),
furnaceCountText(window, getOffset(8)+60, 210, std::to_string(getFurnaceCount()))
{
    // Updating texts
    for (int i=startStep; i < endStep; ++i) {
        timeTexts[i*2].setString(std::format("{:.1f}", mechanicalStages[i].getTime()));
        timeTexts[i*2].setPosition({getOffset(i*2), 150.0f});
        countTexts[i*2].setString(std::to_string(mechanicalStages[i].getNeedLathes(partTarget)));
        countTexts[i*2].setPosition({getOffset(i*2), 180.0f});
        timeTexts[i*2+1].setString(std::format("{:.1f}", thermalStages[i].getTime()));
        timeTexts[i*2+1].setPosition({getOffset(i*2+1), 150.0f});
        countTexts[i*2+1].setString(std::to_string(thermalStages[i].getNeedFurnaces(partTarget)));
        countTexts[i*2+1].setPosition({getOffset(i*2+1), 210.0f});
    }
}

constexpr float ProcessPlanner::getOffset(int index) {
    return stepOffset*index+stepStartOffset;
}

void ProcessPlanner::setTargetProduction(float _target) {
    partTarget = _target;
    update();
}

std::string ProcessPlanner::getTargetProduction() {
    return std::format("{:.1f}", partTarget);
}

void ProcessPlanner::update() {
    // Update process parameters
    recalculate();
    // Updating texts
    for (int i=startStep; i < endStep; ++i) {
        timeTexts[i*2].setString(std::format("{:.1f}", mechanicalStages[i].getTime()));
        countTexts[i*2].setString(std::to_string(mechanicalStages[i].getNeedLathes(partTarget)));
        timeTexts[i*2+1].setString(std::format("{:.1f}", thermalStages[i].getTime()));
        countTexts[i*2+1].setString(std::to_string(thermalStages[i].getNeedFurnaces(partTarget)));
    }
    productionTimeText.setText(std::format("{:.1f}", getProductionTime()));
    machineCountText.setText(std::to_string(getLatheCount()));
    furnaceCountText.setText(std::to_string(getFurnaceCount()));
}

void ProcessPlanner::draw(Window& window) {
    for (int i=startStep*2; i < endStep*2; ++i) {
        stepTexts[i].draw(window);
        window.draw(timeTexts[i]);
        window.draw(countTexts[i]);
    }
    timeDescription.draw(window);
    productionTimeText.draw(window);
    machinesDescription.draw(window);
    furnacesDescription.draw(window);
    machineCountText.draw(window);
    furnaceCountText.draw(window);
    summaryText.draw(window);
}
