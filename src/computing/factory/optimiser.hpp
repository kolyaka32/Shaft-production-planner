#pragma once

#include "factory.hpp"


class Area {
private:
    /* data */

public:
    Area();
    Area(int X, int Y, int width, int height);
    int width, height;
    int X, Y;
};


class Optimiser {
private:
    void setType(Cell& cell);
    static void placeWay(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses);

public:
    Optimiser();
    static void optimise(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses);
};
