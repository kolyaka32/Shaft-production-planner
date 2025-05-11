#pragma once

#include "../app/window.hpp"


// Array representing types of equipment
enum class CellType {
    // Type representing unasseseble area
    Void,

    // Type representing empty space
    None,

    // Types for calculations
    Way,

    // Types for storage
    Cargo,

    // Types of machines
    Machine_1,
    Machine_2, 
    Furnace_1,
};

// Size of square side of cell (in pixels)
const float cellSize = 50.f;


// Class for draw textured cells
class CellDrawer {
private:
    const static unsigned spriteCount = 5;
    const sf::Texture textures[spriteCount];
    sf::Sprite sprites[spriteCount];
    bool drawTexture = true;

    sf::Color getColor(CellType type);
    sf::Sprite& getSprite(CellType type);

public:
    CellDrawer();
    ~CellDrawer();
    void switchDrawType();
    void draw(Window& _window, CellType type, sf::Vector2f absPos);
};
