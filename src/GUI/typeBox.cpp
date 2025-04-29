#include "GUI.hpp"



GUI::TypeBox::TypeBox(Window& window)
: text(window.font) {
    text.setString("123");
}

GUI::TypeBox::~TypeBox() {

}

void GUI::TypeBox::draw(Window& window) {
    window.draw(text);
}
