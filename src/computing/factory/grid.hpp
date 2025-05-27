#pragma once

#include "field.hpp"
#include "../product/productProcess.hpp"


// Class for draw and calculate objects at the grid
class Grid {
private:
    // Absolute position of first element
    const sf::Vector2f pos;
    // Counter indicators
    sf::Text machineCountText, furnaceCountText, cargoCountText;
    // Warnings
    GUI::WarningBox machineCountHigh, furnaceCountHigh, cargoCountHigh;
    GUI::WarningBox machineCountLow, furnaceCountLow, cargoCountLow;
    //
    static void recalculateCellsCount();

protected:
    // Main field [height*width], filled with cells
    static Field field;
    // Counters of current objects at field
    static int machineCount, furnaceCount, cargoCount;
    // Function for update texts
    void updateMachineText();
    void updateFurnaceText();
    void updateCargoText();

    // Getting local position (in cells) from absolute coordinate
    sf::Vector2i getLocal(sf::Vector2i absPos);
    // Getting absolute position (in pixels) from local coordinate
    sf::Vector2f getAbs(sf::Vector2i localPos);
    

public:
    Grid(Window& window, sf::Vector2f position);
    void blit(Window& window);
    bool isSelected(sf::Vector2i pos);
    static void setWidth(unsigned width);
    static void setHeight(unsigned height);
    static std::string getWidth();
    static std::string getHeight();
    static void save(std::ofstream& fout);
    static void load(std::ifstream& fin);
};
