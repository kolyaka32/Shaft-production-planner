#include "factory.hpp"


Factory::Factory(unsigned _W, unsigned _H, sf::Vector2f _pos)
: Grid(_W, _H, _pos) {

}

Factory::~Factory() {

}

void Factory::draw(Window& window) {
    // Draw back part with grid
    blit(window);

    // Draw front objects
    for (auto t : machines) {
        t.draw(window);
    }
}

void Factory::add(Cell::Type _type, sf::Vector2i absPos) {
    // Create new object
    Machinery machine{_type, getLocal(absPos), pos};
    // Check if all cells are avaliable to place
    bool avaliable = true;
    for (int y = machine.getCoord().y; y < machine.getCoord().y+machine.getSizes().y; ++y) {
        for (int x = machine.getCoord().x; x < machine.getCoord().x+machine.getSizes().x; ++x) {
            if (getCell(x, y).getType() != Cell::Type::None) {
                avaliable = false;
            }
        }
    }
    if (avaliable) {
        machines.push_back(machine);
        // Setting cells under machine to it type
        for (int y = machine.getCoord().y; y < machine.getCoord().y+machine.getSizes().y; ++y) {
            for (int x = machine.getCoord().x; x < machine.getCoord().x+machine.getSizes().x; ++x) {
                setCell(x, y, machine.getType());
            }
        }
    }
}

void Factory::remove(sf::Vector2i position) {
    for (int i=0; i < machines.size(); ++i) {
        if (machines[i].at(position)) {
            Machinery& t = machines[i];
            // Resetting cells under that machine
            for (int y = t.getCoord().y; y < t.getCoord().y+t.getSizes().y; ++y) {
                for (int x = t.getCoord().x; x < t.getCoord().x+t.getSizes().x; ++x) {
                    setCell(x, y, Cell::Type::None);
                }
            }
            // Removing machine from list
            machines.erase(machines.begin()+i);
        }
    }
}
