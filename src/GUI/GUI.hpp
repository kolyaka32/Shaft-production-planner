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
        // Inputing text info
        const unsigned maxLength;  // Length of string, that we contain
        const int charSize;        // Size of character in pixels
        sf::Text drawText;
        //std::string currentText;

        // Selection info
        bool selected = false;
        bool pressed = false;

        // Caret and select data info
        int caret;
        int selectLength;
        // Caret draw info
        bool showCaret = false;
        sf::Clock clock;
        sf::Time updateTime;
        sf::RectangleShape drawCaret;

        // Inverse text and it background
        sf::Text inverseText;
        sf::RectangleShape inverseRect;

        // Background
        sf::RectangleShape backGround;

    protected:
        bool in(sf::Vector2i point);

     public:
        TypeBox(Window& window, float X, float Y, unsigned maxLength = 20, std::string startText = "");
        ~TypeBox();
        // Getting input
        void click(sf::Vector2i point);
        void unClick();
        void keyPress(sf::Event::KeyPressed state);
        void inputText(char32_t ch);
        void update(sf::Vector2i point);
        // Drawing at screen
        void draw(Window& window);
        // Getting entered text
        std::string getString();
        float getNumber();
    };
};
