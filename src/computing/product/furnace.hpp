#pragma once


// Class representing single furnace and it properties
class Furnace {
private:
    float diameter;

public:
    Furnace(float diameter);
    unsigned getMaxParts();
};
