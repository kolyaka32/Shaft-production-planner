#include "grid.hpp"


// Static class values
Field Grid::field{10, 5};


Grid::Grid(sf::Vector2f _pos)
: pos(_pos) {}

sf::Vector2i Grid::getLocal(sf::Vector2i absPos) {
    return {int((absPos.x-pos.x)/cellSize), int((absPos.y-pos.y)/cellSize)};
}

sf::Vector2f Grid::getAbs(sf::Vector2i localPos) {
    return {localPos.x*cellSize + pos.x, localPos.y*cellSize + pos.y};
}

void Grid::blit(Window& window) {
    sf::RectangleShape square({cellSize, cellSize});
    square.setPosition(pos);

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
}
