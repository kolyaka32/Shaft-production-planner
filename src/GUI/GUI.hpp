#pragma once

#include <vector>
#include <string>
#include "../app/window.hpp"


namespace GUI {
    class Text {
     private:
        LanguagedText texts;
        sf::Text text;

     public:
        Text(Window& window, float X, float Y, LanguagedText texts);
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
        void draw(Window& window);
    };


    class ImageButton {
     private:
        const sf::Texture texture;
        sf::Sprite sprite;

     public:
        ImageButton(float X, float Y, float W, float H, const std::string fileName);
        ImageButton(float X, float Y, const std::string fileName);
        bool isClicked(sf::Vector2i point);
        void draw(Window& window);
    };


    class InfoBox {
     private:
        unsigned counter = 0;
        sf::Color color = sf::Color::White;
        sf::Text text;

     public:
        InfoBox(Window& window, float X, float Y, LanguagedText texts);
        void draw(Window& window);
        void reset();
    };

    class WarningBox {
     private:
        sf::Text text;
		const sf::Texture texture;
        sf::Sprite sprite;
		bool active = false;

     public:
      	WarningBox(Window& window, float X, float Y, LanguagedText texts, const std::string imageFile);
		void draw(Window& window);
		void activate();
		void deactivate();
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
        bool keyPress(sf::Event::KeyPressed state);
        void inputText(char32_t ch);
        void update(sf::Vector2i point);
        // Drawing at screen
        void draw(Window& window);
        // Getting entered text
        void setString(std::string str);
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
        SwitchBox(Window& window, float X, float Y, LanguagedText texts[count], unsigned startOption = 0);
        void draw(Window& window);
        bool click(sf::Vector2i point);  // return true, when entered new value
        void set(unsigned value);
        unsigned getValue();
    };

}; // Namespace GUI
