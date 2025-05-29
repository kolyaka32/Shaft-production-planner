#include "grid.hpp"


// Static class values
Field Grid::field{10, 5};
int Grid::latheCount = 0;
int Grid::furnaceCount = 0;
int Grid::warehouseCount = 0;


Grid::Grid(Window& window, sf::Vector2f _pos)
: pos(_pos),
latheCountText(window.font),
furnaceCountText(window.font),
warehouseCountText(window.font),
latheCountHigh(window, 700, 60,  {"Number of machines is excessive", "Число станков избыточно"}, "machines/warning-icon.png"),
furnaceCountHigh(window, 700, 100, {"Number of furnaces is excessive", "Число печей избыточно"}, "machines/warning-icon.png"),
warehouseCountHigh(window,   700, 140, {"Number of warehouses is excessive", "Число складов избыточно"}, "machines/warning-icon.png"),
latheCountLow(window,  700, 60,  {"Number of machines is insufficient", "Число станков недостаточно"}, "machines/warning-icon.png"),
furnaceCountLow(window,  700, 100, {"Number of furnaces is insufficient", "Число печей недостаточно"}, "machines/warning-icon.png"),
warehouseCountLow(window,    700, 140, {"Number of warehouses is insufficient", "Число складов недостаточно"}, "machines/warning-icon.png") {
    // Placing texts
    latheCountText.setPosition({280, 60});
    furnaceCountText.setPosition({280, 100});
    warehouseCountText.setPosition({280, 140});
    updateLatheText();
    updateFurnaceText();
    updateWarehouseText();
}

sf::Vector2i Grid::getLocal(sf::Vector2i absPos) {
    return {int((absPos.x-pos.x)/cellSize), int((absPos.y-pos.y)/cellSize)};
}

sf::Vector2f Grid::getAbs(sf::Vector2i localPos) {
    return {localPos.x*cellSize + pos.x, localPos.y*cellSize + pos.y};
}

void Grid::updateLatheText() {
    // Update text itself
    std::string str;
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        str = std::format("Lathes: {}, needed: {}", latheCount, ProcessPlanner::getLatheCount());
        break;
    
    case Language::Russian:
        str = std::format("Станков: {}, необходимо: {}", latheCount, ProcessPlanner::getLatheCount());
        break;
    }
    latheCountText.setString(sf::String::fromUtf8(str.begin(), str.end()));
    // Update warnings
    latheCountHigh.deactivate();
    latheCountLow.deactivate();
    if (latheCount > ProcessPlanner::getLatheCount()) {
        latheCountHigh.activate();
    } else if (latheCount < ProcessPlanner::getLatheCount()) {
        latheCountLow.activate();
    }
}

void Grid::updateFurnaceText() {
    // Update text itself
    std::string str;
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        str = std::format("Furnaces: {}, needed: {}", furnaceCount, ProcessPlanner::getFurnaceCount());
        break;
    
    case Language::Russian:
        str = std::format("Печей: {}, необходимо: {}", furnaceCount, ProcessPlanner::getFurnaceCount());
        break;
    }
    furnaceCountText.setString(sf::String::fromUtf8(str.begin(), str.end()));
    // Update warnings
    furnaceCountHigh.deactivate();
    furnaceCountLow.deactivate();
    if (furnaceCount > ProcessPlanner::getFurnaceCount()) {
        furnaceCountHigh.activate();
    } else if (furnaceCount < ProcessPlanner::getFurnaceCount()) {
        furnaceCountLow.activate();
    }
}

void Grid::updateWarehouseText() {
    // Update text itself
    std::string str;
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        str = std::format("Warehouses: {}, needed: {}", warehouseCount, ProcessPlanner::getWarehouseCount());
        break;
    
    case Language::Russian:
        str = std::format("Складов: {}, необходимо: {}", warehouseCount, ProcessPlanner::getWarehouseCount());
        break;
    }
    warehouseCountText.setString(sf::String::fromUtf8(str.begin(), str.end()));
    // Update warnings
    warehouseCountHigh.deactivate();
    warehouseCountLow.deactivate();
    if (warehouseCount > ProcessPlanner::getWarehouseCount()) {
        warehouseCountHigh.activate();
    } else if (warehouseCount < ProcessPlanner::getWarehouseCount()) {
        warehouseCountLow.activate();
    }
}

void Grid::recalculateCellsCount() {
    // Resetting counts
    latheCount=0;
    furnaceCount=0;
    warehouseCount=0;

    // Couting all objects
    for (int i=0; i < field.getHeight()*field.getWidth(); ++i) {
        switch (field[i].getType()) {
        case CellType::Lathe_1:
        case CellType::Lathe_2:
            latheCount++;
            break;

        case CellType::Furnace_1:
            furnaceCount++;
            break;

        case CellType::Warehouse:
            warehouseCount++;
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
    window.draw(latheCountText);
    window.draw(furnaceCountText);
    window.draw(warehouseCountText);
    latheCountHigh.draw(window);
    furnaceCountHigh.draw(window);
    warehouseCountHigh.draw(window);
    latheCountLow.draw(window);
    furnaceCountLow.draw(window);
    warehouseCountLow.draw(window);

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
