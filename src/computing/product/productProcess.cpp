#include "productProcess.hpp"


ProductProcess::ProductProcess(Window& window)
: drawSemiproducts {
    {window,  20, 540},
    {window, 250, 540},
    {window, 480, 540},
    {window, 710, 540},
    {window, 940, 540}},
drawSteps {
    {window, 170, 540, {"Rough", "Черновая"}},
    {window, 400, 540, {"Main", "Получистовая"}},
    {window, 630, 540, {"Trimming", "Чистовая"}},
    {window, 860, 540, {"Finishing", "Отделочная"}}},
warningLowLength(window, 750, 350, {"Insufficient length", "Недостаточная длинна"}, "machines/danger-icon.png"),
warningLowDiameter(window, 750, 400, {"Insufficient diameter", "Недостаточный диаметр"}, "machines/danger-icon.png"),
warningHighLength(window, 750, 350, {"Redundant length", "Избыточная длинна"}, "machines/warning-icon.png"),
warningHighDiameter(window, 750, 400, {"Redundant diameter", "Избыточный диаметр"}, "machines/warning-icon.png"),
warningHighBlankRoughness(window, 750, 450, {"Too low blank rougness", "Слишком малая шероховатость"}, "machines/warning-icon.png") {
    // Update on creation
    update();
}

void ProductProcess::setTargetRoughness(float _targetRoughness) {
    targetPart.rougness = _targetRoughness;
    update();
}

void ProductProcess::setTargetDiameter(float _targetDiameter) {
    targetPart.diameter = _targetDiameter;
    update();
}

void ProductProcess::setTargetLength(float _targetLength) {
    targetPart.length = _targetLength;
    update();
}

void ProductProcess::setBlankRoughness(float _roughness) {
    blankPart.rougness = _roughness;
    update();
}

void ProductProcess::setBlankDiameter(float _diameter) {
    blankPart.diameter = _diameter;
    update();
}

void ProductProcess::setBlankLength(float _length) {
    blankPart.length = _length;
    update();
}

void ProductProcess::setMaterial(unsigned _index) {
    Part::material = Material(_index);
    update();
}

unsigned ProductProcess::getMaterial() {
    return Part::material;
}

std::string ProductProcess::getTargetRoughness() {
    return std::format("{:.1f}", targetPart.rougness);
}

std::string ProductProcess::getTargetLength() {
    return std::format("{:.0f}", targetPart.length);
}

std::string ProductProcess::getTargetDiameter() {
    return std::format("{:.1f}", targetPart.diameter);
}

std::string ProductProcess::getBlankRoughness() {
    return std::format("{:.1f}", blankPart.rougness);
}

std::string ProductProcess::getBlankLength() {
    return std::format("{:.0f}", blankPart.length);
}

std::string ProductProcess::getBlankDiameter() {
    return std::format("{:.1f}", blankPart.diameter);
}

void ProductProcess::update() {
    // Resetting warnings
    warningLowLength.deactivate();
    warningLowDiameter.deactivate();
    warningHighLength.deactivate();
    warningHighDiameter.deactivate();
    warningHighBlankRoughness.deactivate();

    // Recalculating process
    recalculate();

    // Reactivating warnings
    if (blankPart.rougness < targetPart.rougness) {
        warningHighBlankRoughness.activate();
    }
    // Checking, if blank parameters allowable and optimal
    const Part& calcBlank = semiproducts[startStep];
    if (calcBlank.length > blankPart.length) {
        warningLowLength.activate();
    } else if (blankPart.length > calcBlank.length*1.2) {
        warningHighLength.activate();
    }
    if (calcBlank.diameter > blankPart.diameter) {
        warningLowDiameter.activate();
    } else if (blankPart.diameter > calcBlank.diameter*1.2) {
        warningHighDiameter.activate();
    }
    // Updating semiproducts
    for (int i=endStep; i >= startStep; --i) {
        drawSemiproducts[i].setNewParameters(semiproducts[i]);
    }
}

void ProductProcess::draw(Window& window) {
    // Draw main steps
    for (int i=startStep; i <= endStep; ++i) {
        drawSemiproducts[i].draw(window);
    }
    for (int i=startStep; i < endStep; ++i) {
        drawSteps[i].draw(window);
    }
    // Draw warnings
    warningLowLength.draw(window);
    warningLowDiameter.draw(window);
    warningHighLength.draw(window);
    warningHighDiameter.draw(window);
    warningHighBlankRoughness.draw(window);
}


void ProductProcess::save(std::ofstream& fout) {
    // Writing system data
    fout << '\n';
    fout << "Part\n";
    // Writing part data
    fout << targetPart.diameter << ' ' << targetPart.length << ' ' << targetPart.rougness << '\n';

    // Writing blank data
    fout << blankPart.diameter << ' ' << blankPart.length << ' ' << blankPart.rougness << '\n';

    // Writing other part data
    fout << Part::material << '\n';
}

void ProductProcess::load(std::ifstream& fin) {
    // Current reading line
    std::string line;

    // Skipping first 2 lines (empty and title)
    std::getline(fin, line);
    std::getline(fin, line);

    // Getting part data
    fin >> targetPart.diameter >> targetPart.length >> targetPart.rougness;

    // Getting blank data
    fin >> blankPart.length >> blankPart.length >> blankPart.rougness;

    // Getting other part data
    unsigned index;
    fin >> index;
    Part::material = Material{index};

    // Recalculating all values and processes
    recalculate();
}
