#include "cell.hpp"


// Class representing
class CursorMachine {
protected:
    Cell::Type type = Cell::Type::None;
    sf::RectangleShape rect;

public:
    CursorMachine();
    ~CursorMachine();
    void setType(Cell::Type type);
    void draw(Window& window, sf::Vector2i pos);
    Cell::Type getType();
};
