#include "cellDrawer.hpp"
#include "../testing.hpp"



CellDrawer::CellDrawer()
: textures {
    {(sf::Texture)(resourcesDir() / "machines/tile.png")},
    {(sf::Texture)(resourcesDir() / "machines/cargo1.png")},
    {(sf::Texture)(resourcesDir() / "machines/machine1.png")},
    {(sf::Texture)(resourcesDir() / "machines/machine2.png")},
    {(sf::Texture)(resourcesDir() / "machines/machine3.png")},
},
sprites {
    {(sf::Sprite)textures[0]},
    {(sf::Sprite)textures[1]},
    {(sf::Sprite)textures[2]},
    {(sf::Sprite)textures[3]},
    {(sf::Sprite)textures[4]},
} {
    // Setting sizes of all sprites
    for (int i=0; i < spriteCount; ++i) {
        sprites[i].setScale({cellSize/320, cellSize/320});
    }
}

CellDrawer::~CellDrawer() {

}

sf::Color CellDrawer::getColor(Cell::Type type) {
    switch (type) {
    case Cell::Type::None:
        return sf::Color::White;

    case Cell::Type::Way:
        return sf::Color::Yellow;

    case Cell::Type::Machine_1:
        return sf::Color::Red;

    case Cell::Type::Machine_2:
        return sf::Color::Blue;

    case Cell::Type::Furnace_1:
        return sf::Color::Cyan;
    
    default:
        return sf::Color{100};
    }
}

sf::Sprite& CellDrawer::getSprite(Cell::Type type) {
    return sprites[(int)type-2];
}

void CellDrawer::switchDrawType() {
    drawTexture ^= true;
}

void CellDrawer::draw(Window& window, Cell::Type type, sf::Vector2f absPos) {
    if (drawTexture && type != Cell::Type::None && type != Cell::Type::Void) {
        // Drawing cell as sprite with texture
        getSprite(type).setPosition(absPos);
        window.draw(getSprite(type));
    } else {
        // Draw cell as rect with color
        sf::RectangleShape shape({cellSize, cellSize});
        shape.setFillColor(getColor(type));
        shape.setPosition(absPos);
        window.draw(shape);
    }
}
