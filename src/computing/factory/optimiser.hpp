#pragma once

#include "factory.hpp"


class Optimiser {
private:
    static void placeWay(Field& field, unsigned count);
    static bool connectCell(Field& copy, unsigned index, unsigned& counter);
    static bool findWay(Field& copy, int& step, int& findCellX, int& findCellY, unsigned& findIndex, unsigned startIndex);
    static void setCell(Field& field, int X, int Y, unsigned weight);
    static bool trySetWay(Field& field, int X, int Y, unsigned weight, unsigned& counter);
    static void tryPlaceMachine(Field& field, int X, int Y, unsigned& counter);

public:
    Optimiser();
    static void optimise(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses);
};
