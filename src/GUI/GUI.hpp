#pragma once

#include "../app/window.hpp"
#include <vector>
#include <string>


namespace GUI {
    class Text {
    private:
        LanguagedText texts;
        sf::Text text;

    public:
        Text(Window& window, float X, float Y, LanguagedText texts);
        void update(Window& window);
        void draw(Window& window);
    };
    
    class TextButton {
    private:
        LanguagedText texts;
        sf::RectangleShape rect;
        sf::Text text;

    public:
        TextButton(Window& window, float X, float Y, float W, float H, LanguagedText texts);
        bool isClicked(sf::Vector2i point);
        void update(Window& window);
        void draw(Window& window);
    };


    class ImageButton {
    private:
        const sf::Texture texture;
        sf::Sprite sprite;

    public:
        ImageButton(float X, float Y, float W, float H, const std::string fileName);
        bool isClicked(sf::Vector2i point);
        void draw(Window& window);
    };


    class InfoBox {
    private:
        LanguagedText texts;
        unsigned counter = 0;
        sf::Color color = sf::Color::White;
        sf::Text text;

    public:
        InfoBox(Window& window, float X, float Y, LanguagedText texts);
        void draw(Window& window);
        void update(Window& window);
        void reset();
    };


    class TypeBox {
     private:
        // Inputing text info
        sf::Text drawText;

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

        void clearSelected(const sf::String& str);
        void updateInversePos();

     public:
        TypeBox(Window& window, float X, float Y, float W, std::string startText = "");
        // Getting input
        bool click(sf::Vector2i point);  // Return true, when stop inputing
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

    // Class for selecting variants from list
    template <unsigned count>
    class SwitchBox {
    private:
        unsigned selected = 0;
        bool opened = false;
        // Draw options
        std::vector<sf::Text> drawnTexts;
        sf::RectangleShape backgroundBox;

    public:
        SwitchBox(Window& window, float X, float Y, LanguagedText texts[count]);
        void draw(Window& window);
        bool click(sf::Vector2i point);  // return true, when entered new value
    };
    
}; // Namespace GUI
