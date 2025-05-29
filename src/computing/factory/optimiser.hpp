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
    void solve(Field& field);
};
