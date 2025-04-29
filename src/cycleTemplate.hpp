#pragma once

#include "window.hpp"
#include "GUI/GUI.hpp"

// Template class for create and run cycles
class CycleTemplate {
    private:
        void getInput(Window& window);
    
    protected:
        virtual void keyDown(sf::Keyboard::Key key, Window& window) {};
        virtual void mouseClick(Window& window) {};
        virtual void mouseUnClick(Window& window) {};
        virtual void update(Window& window) {};
        virtual void draw(Window& window) {};
    
    public:
        CycleTemplate();
        ~CycleTemplate();
        void run(Window& window);
    };
    