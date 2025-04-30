#pragma once

#include "../window.hpp"
#include <vector>
#include <string>


namespace GUI {
    class Button {
    private:
        const std::vector<std::string> texts;
        sf::RectangleShape rect;
        sf::Text text;

    public:
        Button(Window& window, float X, float Y, float W, float H, const std::vector<std::string>);
        ~Button();
        bool isClicked(sf::Vector2i point);
        void update(Window& window);
        void draw(Window& window);
    };

    class TypeBox {
     private:
        sf::Text text;

     public:
        TypeBox(Window& window);
        ~TypeBox();
        void draw(Window& window);
    };
};
