#include "productProcess.hpp"


// Static global process options
Part ProductProcess::targetPart{60, 200, 4};
Part ProductProcess::blanktPart{80, 220, 240};


ProductProcess::ProductProcess(Window& window)
: semiproducts {
    {window,  20, 540},
    {window, 250, 540},
    {window, 480, 540},
    {window, 710, 540},
    {window, 940, 540}},
steps {
    {window, 170, 540, {"Rough", "Черновая"}},
    {window, 400, 540, {"Main", "Получистовая"}},
    {window, 630, 540, {"Trimming", "Чистовая"}},
    {window, 860, 540, {"Finishing", "Отделочная"}}},
warningLowLength(window, 750, 350, {"Insufficient length", "Недостаточная длинна"}, "machines/danger-icon.png"),
warningLowDiameter(window, 750, 400, {"Insufficient diameter", "Недостаточный диаметр"}, "machines/danger-icon.png"),
warningHighLength(window, 750, 350, {"Redundant length", "Избыточная длинна"}, "machines/warning-icon.png"),
warningHighDiameter(window, 750, 400, {"Redundant diameter", "Избыточный диаметр"}, "machines/warning-icon.png"),
warningHighBlankRoughness(window, 750, 450, {"Too low blank rougness", "Слишком малая шероховатость"}, "machines/warning-icon.png") {}

void ProductProcess::setTargetRoughness(float _targetRoughness) {
    targetPart.rougness = _targetRoughness;
    recalculate(targetPart, blanktPart);
}

void ProductProcess::setTargetDiameter(float _targetDiameter) {
    targetPart.diameter = _targetDiameter;
    recalculate(targetPart, blanktPart);
}

void ProductProcess::setTargetLength(float _targetLength) {
    targetPart.length = _targetLength;
    recalculate(targetPart, blanktPart);
}

void ProductProcess::setBlankRoughness(float _roughness) {
    blanktPart.rougness = _roughness;
    recalculate(targetPart, blanktPart);
}

void ProductProcess::setBlankDiameter(float _diameter) {
    blanktPart.diameter = _diameter;
    recalculate(targetPart, blanktPart);
}

void ProductProcess::setBlankLength(float _length) {
    blanktPart.length = _length;
    recalculate(targetPart, blanktPart);
}

void ProductProcess::setMaterial(unsigned _index) {
    Part::material = Material(_index);
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
    return std::format("{:.1f}", blanktPart.rougness);
}

std::string ProductProcess::getBlankLength() {
    return std::format("{:.0f}", blanktPart.length);
}

std::string ProductProcess::getBlankDiameter() {
    return std::format("{:.1f}", blanktPart.diameter);
}


void ProductProcess::draw(Window& window) {
    // Draw main steps
    for (int i=startStep; i <= stepCount; ++i) {
        semiproducts[i].draw(window);
    }
    for (int i=startStep; i < stepCount; ++i) {
        steps[i].draw(window);
    }
    // Draw warnings
    warningLowLength.draw(window);
    warningLowDiameter.draw(window);
    warningHighLength.draw(window);
    warningHighDiameter.draw(window);
    warningHighBlankRoughness.draw(window);
}


/*void ProductProcess::recalculate() {
    // Resetting warnings
    warningLowLength.deactivate();
    warningLowDiameter.deactivate();
    warningHighLength.deactivate();
    warningHighDiameter.deactivate();
    warningHighBlankRoughness.deactivate();

    // Update step count
    stepCount = getStepCount(targetRoughness)+1;
    
    if (blankRoughness < targetRoughness) {
        startStep = stepCount-1;
        warningHighBlankRoughness.activate();
    } else {
        startStep = getStepCount(blankRoughness);
        // Check, if at same step
        if (startStep+1 == stepCount) {
            startStep = stepCount-1;
        }
    }

    // Update input diameters
    float inputDiameter = targetDiameter;
    float inputLength = targetLength;
    for (int i=stepCount; i > startStep; --i) {
        semiproducts[i].setNewParameters(inputDiameter, inputLength, material);
        inputDiameter = getInputDiameter(i, inputDiameter);
        inputLength = getInputLength(i, inputLength);
    }
    // Update extra blank object
    semiproducts[0].setNewParameters(inputDiameter, inputLength, material);

    // Checking, if blank parameters allowable and optimal
    if (inputLength > blankLength) {
        warningLowLength.activate();
    } else if (blankLength > inputLength*1.2) {
        warningHighLength.activate();
    }
    if (inputDiameter > blankDiameter) {
        warningLowDiameter.activate();
    } else if (blankDiameter > inputDiameter*1.2) {
        warningHighDiameter.activate();
    }
}*/


void ProductProcess::save(std::ofstream& fout) {
    // Writing system data
    fout << '\n';
    fout << "Part\n";
    // Writing part data
    fout << targetPart.diameter << ' ' << targetPart.length << ' ' << targetPart.rougness << '\n';

    // Writing blank data
    fout << blanktPart.diameter << ' ' << blanktPart.length << ' ' << blanktPart.rougness << '\n';

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
    fin >> blanktPart.length >> blanktPart.length >> blanktPart.rougness;

    // Getting other part data
    unsigned index;
    fin >> index;
    Part::material = Material{index};

    // Recalculating all values and processes
    recalculate(targetPart, blanktPart);
}
