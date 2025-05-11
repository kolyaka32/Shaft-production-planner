#pragma once

#include "cell.hpp"

// Class for draw textured cells
class CellDrawer {
private:
    const static unsigned spriteCount = 5;
    const sf::Texture textures[spriteCount];
    sf::Sprite sprites[spriteCount];
    bool drawTexture = true;

    sf::Color getColor(Cell::Type type);
    sf::Sprite& getSprite(Cell::Type type);

public:
    CellDrawer();
    ~CellDrawer();
    void switchDrawType();
    void draw(Window& _window, Cell::Type type, sf::Vector2f absPos);
};
