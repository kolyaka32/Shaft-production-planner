#include "grid.hpp"


// Static class values
Field Grid::field{10, 5};
int Grid::machineCount = 0;
int Grid::furnaceCount = 0;
int Grid::cargoCount = 0;


Grid::Grid(Window& window, sf::Vector2f _pos)
: pos(_pos),
machineCountText(window.font),
furnaceCountText(window.font),
cargoCountText(window.font),
machineCountHigh(window, 700, 60,  {"Number of machines is excessive", "Число станков избыточно"}, "machines/warning-icon.png"),
furnaceCountHigh(window, 700, 100, {"Number of furnaces is excessive", "Число печей избыточно"}, "machines/warning-icon.png"),
cargoCountHigh(window,   700, 140, {"Number of warehouses is excessive", "Число складов избыточно"}, "machines/warning-icon.png"),
machineCountLow(window,  700, 60,  {"Number of machines is insufficient", "Число станков недостаточно"}, "machines/warning-icon.png"),
furnaceCountLow(window,  700, 100, {"Number of furnaces is insufficient", "Число печей недостаточно"}, "machines/warning-icon.png"),
cargoCountLow(window,    700, 140, {"Number of warehouses is insufficient", "Число складов недостаточно"}, "machines/warning-icon.png") {
    // Placing texts
    machineCountText.setPosition({280, 60});
    furnaceCountText.setPosition({280, 100});
    cargoCountText.setPosition({280, 140});
    updateMachineText();
    updateFurnaceText();
    updateCargoText();
}

sf::Vector2i Grid::getLocal(sf::Vector2i absPos) {
    return {int((absPos.x-pos.x)/cellSize), int((absPos.y-pos.y)/cellSize)};
}

sf::Vector2f Grid::getAbs(sf::Vector2i localPos) {
    return {localPos.x*cellSize + pos.x, localPos.y*cellSize + pos.y};
}

void Grid::updateMachineText() {
    // Update text itself
    std::string str;
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        str = std::format("Machines: {}, needed: {}", machineCount, ProductProcess::getMachineCount());
        break;
    
    case Language::Russian:
        str = std::format("Станков: {}, необходимо: {}", machineCount, ProductProcess::getMachineCount());
        break;
    }
    machineCountText.setString(sf::String::fromUtf8(str.begin(), str.end()));
    // Update warnings
    machineCountHigh.deactivate();
    machineCountLow.deactivate();
    if (machineCount > ProductProcess::getMachineCount()) {
        machineCountHigh.activate();
    } else if (machineCount < ProductProcess::getMachineCount()) {
        machineCountLow.activate();
    }
}

void Grid::updateFurnaceText() {
    // Update text itself
    std::string str;
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        str = std::format("Furnaces: {}, needed: {}", furnaceCount, ProductProcess::getMachineCount());
        break;
    
    case Language::Russian:
        str = std::format("Печей: {}, необходимо: {}", furnaceCount, ProductProcess::getMachineCount());
        break;
    }
    furnaceCountText.setString(sf::String::fromUtf8(str.begin(), str.end()));
    // Update warnings
    furnaceCountHigh.deactivate();
    furnaceCountLow.deactivate();
    if (furnaceCount > ProductProcess::getMachineCount()) {
        furnaceCountHigh.activate();
    } else if (furnaceCount < ProductProcess::getMachineCount()) {
        furnaceCountLow.activate();
    }
}

void Grid::updateCargoText() {
    // Update text itself
    std::string str;
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        str = std::format("Warehouses: {}, needed: {}", cargoCount, ProductProcess::getMachineCount());
        break;
    
    case Language::Russian:
        str = std::format("Складов: {}, необходимо: {}", cargoCount, ProductProcess::getMachineCount());
        break;
    }
    cargoCountText.setString(sf::String::fromUtf8(str.begin(), str.end()));
    // Update warnings
    cargoCountHigh.deactivate();
    cargoCountLow.deactivate();
    if (cargoCount > ProductProcess::getMachineCount()) {
        cargoCountHigh.activate();
    } else if (cargoCount < ProductProcess::getMachineCount()) {
        cargoCountLow.activate();
    }
}

void Grid::recalculateCellsCount() {
    // Resetting counts
    machineCount=0;
    furnaceCount=0;
    cargoCount=0;

    // Couting all objects
    for (int i=0; i < field.getHeight()*field.getWidth(); ++i) {
        switch (field[i].getType()) {
        case CellType::Machine_1:
        case CellType::Machine_2:
            machineCount++;
            break;

        case CellType::Furnace_1:
            furnaceCount++;
            break;

        case CellType::Cargo:
            cargoCount++;
            break;
        
        default:
            break;
        }
    }
}

void Grid::blit(Window& window) {
    sf::RectangleShape square({cellSize, cellSize});
    square.setPosition(pos);

    // Draw counters
    window.draw(machineCountText);
    window.draw(furnaceCountText);
    window.draw(cargoCountText);
    machineCountHigh.draw(window);
    furnaceCountHigh.draw(window);
    cargoCountHigh.draw(window);
    machineCountLow.draw(window);
    furnaceCountLow.draw(window);
    cargoCountLow.draw(window);

    // Draw cells
    for (int y=0; y < field.getHeight(); ++y) {
        for (int x=0; x < field.getWidth(); ++x) {
            // Checking, if cell
            if (field.getCell({x, y}).getType() != CellType::Void) {
                field.getCell({x, y}).draw(window, getAbs({x, y}));
            }
            square.move({cellSize, 0});
        }
        square.move({-cellSize*field.getWidth(), cellSize});
    }

    // Draw vertical lines
    sf::Vertex vertLine[] {
        {pos, sf::Color::Black, {0.f, 0.f}},
        {{pos.x, pos.y + cellSize*field.getHeight()}, sf::Color::Black, {0.f, 0.f}}
    };
    for (int x=0; x < field.getWidth()+1; ++x) {
        window.draw(vertLine, 2, sf::PrimitiveType::Lines);
        vertLine[0].position.x += cellSize;
        vertLine[1].position.x += cellSize;
    }

    // Draw horizontal lines
    sf::Vertex horLine[] {
        {pos, sf::Color::Black, {0.f, 0.f}},
        {{pos.x + cellSize*field.getWidth(), pos.y}, sf::Color::Black, {0.f, 0.f}}
    };
    for (int y=0; y < field.getHeight()+1; ++y) {
        window.draw(horLine, 2, sf::PrimitiveType::Lines);
        horLine[0].position.y += cellSize;
        horLine[1].position.y += cellSize;
    }
}

bool Grid::isSelected(sf::Vector2i point) {
    return (pos.x < point.x)
    && (pos.y < point.y)
    && (pos.x + field.getWidth()*cellSize > point.x)
    && (pos.y + field.getHeight()*cellSize > point.y);
}

void Grid::setWidth(unsigned _width) {
    field.setWidth(_width);
}

void Grid::setHeight(unsigned _height) {
    field.setHeight(_height);
}

std::string Grid::getWidth() {
    return std::to_string(field.getWidth());
}

std::string Grid::getHeight() {
    return std::to_string(field.getHeight());
}

void Grid::save(std::ofstream& fout) {
    // Writing system data
    fout << '\n';
    fout << "Grid\n";
    field.save(fout);
}

void Grid::load(std::ifstream& fin) {
    // Current reading line
    std::string line;

    // Skipping first 2 lines (empty and title)
    std::getline(fin, line);
    std::getline(fin, line);

    // Load data to field
    field.load(fin);
    recalculateCellsCount();
}
