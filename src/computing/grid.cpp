#include "grid.hpp"


// Grid realisation
Grid::Grid(unsigned _width, unsigned _height, sf::Vector2f _pos)
: width(_width),
height(_height),
grid(new Cell[_width*_height]),
pos(_pos) {
    // Clearing grid
    for (int i=0; i < _width*_height; ++i) {
        grid[i].setType(CellType::None);
    }
}

Grid::~Grid() {
    delete grid;
}

Cell& Grid::getCell(sf::Vector2i pos) {
    return grid[pos.x + pos.y*width];
}

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
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            // Checking, if cell 
            if (getCell({x, y}).getType() != CellType::Void) {
                getCell({x, y}).draw(window, getAbs({x, y}));
            }
            square.move({cellSize, 0});
        }
        square.move({-cellSize*width, cellSize});
    }

    // Draw vertical lines
    sf::Vertex vertLine[] {
        {pos, sf::Color::Black, {0.f, 0.f}},
        {{pos.x, pos.y + cellSize*height}, sf::Color::Black, {0.f, 0.f}}
    };
    for (int x=0; x < width+1; ++x) {
        window.draw(vertLine, 2, sf::PrimitiveType::Lines);
        vertLine[0].position.x += cellSize;
        vertLine[1].position.x += cellSize;
    }

    // Draw horizontal lines
    sf::Vertex horLine[] {
        {pos, sf::Color::Black, {0.f, 0.f}},
        {{pos.x + cellSize*width, pos.y}, sf::Color::Black, {0.f, 0.f}}
    };
    for (int y=0; y < height+1; ++y) {
        window.draw(horLine, 2, sf::PrimitiveType::Lines);
        horLine[0].position.y += cellSize;
        horLine[1].position.y += cellSize;
    }
}

bool Grid::isSelected(sf::Vector2i point) {
    return (pos.x < point.x)
    && (pos.y < point.y)
    && (pos.x + width*cellSize > point.x)
    && (pos.y + height*cellSize > point.y);
}
