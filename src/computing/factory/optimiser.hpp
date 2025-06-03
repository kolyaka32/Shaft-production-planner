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
    static void placeWay(Field& field, unsigned count);
    static bool connectCell(Field& copy, sf::Vector2i cell, unsigned& counter);

public:
    Optimiser();
    static void optimise(Field& field, unsigned lathe, unsigned furnace, unsigned warehouses);
};
