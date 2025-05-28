#include "cellDrawer.hpp"


CellDrawer::CellDrawer()
: textures {
    {(sf::Texture)(resourcesDir() / "machines/tile.png")},
    {(sf::Texture)(resourcesDir() / "machines/cargo1.png")},
    {(sf::Texture)(resourcesDir() / "machines/machine1.png")},
    {(sf::Texture)(resourcesDir() / "machines/machine2.png")},
    {(sf::Texture)(resourcesDir() / "machines/machine3.png")}},
warningTexture(resourcesDir() / "machines/no-path-icon.png"),
sprites {
    {(sf::Sprite)textures[0]},
    {(sf::Sprite)textures[1]},
    {(sf::Sprite)textures[2]},
    {(sf::Sprite)textures[3]},
    {(sf::Sprite)textures[4]}},
warningSprite(warningTexture) {
    // Setting sizes of all sprites
    for (int i=0; i < spriteCount; ++i) {
        sprites[i].setScale({cellSize/320, cellSize/320});
    }
    // Also warning sign
    //warningSprite.setOrigin({cellSize/2,cellSize/2});
}

sf::Color CellDrawer::getColor(CellType type) {
    switch (type) {
    case CellType::None:
        return sf::Color::White;

    case CellType::Way:
        return sf::Color::Yellow;

    case CellType::Lathe_1:
        return sf::Color::Red;

    case CellType::Lathe_2:
        return sf::Color::Blue;

    case CellType::Furnace_1:
        return sf::Color::Cyan;
    
    default:
        return sf::Color{100};
    }
}

sf::Sprite& CellDrawer::getSprite(CellType type) {
    return sprites[(int)type-2];
}

void CellDrawer::switchDrawType() {
    drawTexture ^= true;
}

void CellDrawer::draw(Window& window, CellType type, sf::Vector2f absPos) {
    if (drawTexture && type != CellType::None && type != CellType::Void) {
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

void CellDrawer::drawWarning(Window& window, sf::Vector2f absPos) {
    if (drawTexture) {
        // Draw warning sprite
        warningSprite.setPosition(absPos);
        window.draw(warningSprite);
    }
}
