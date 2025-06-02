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
    /* data */

public:
    Optimiser();
    static void placeWay(Field& field, unsigned count);
    static void placeObjects(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses);
};
