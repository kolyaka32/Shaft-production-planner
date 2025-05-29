#pragma once

#include "grid.hpp"


// Class representing whole workshop
class Factory : public Grid {
public:
    Factory(Window& window, sf::Vector2f pos);
    void draw(Window& window);
    void set(CellType type, sf::Vector2i absPos);
    void remove(sf::Vector2i absPos);
    void reset(sf::Vector2i absPos);
    static bool checkConnections();
    void tryOptimize();

private:
    static void indexConnected(sf::Vector2i pos, unsigned index);
};
