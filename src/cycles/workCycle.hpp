#pragma once

#include "../app/cycleTemplate.hpp"
#include "../computing/factory/factorySubWindow.hpp"
#include "../computing/product.hpp/productSubWindow.hpp"


// Template class for create and run cycles
class WorkCycle : public CycleTemplate {
private:
    // Subwindows for separate work on different parts of projecting
    enum class currentWindow {
        Product,
        Factory,
    };
    // Current selected subwindow to work with
    currentWindow target = currentWindow::Product;
    // All subwindows
    ProductSubWindow product;
    FactorySubWindow factory;

    // Buttons for switch between subwindows
    GUI::TextButton selectProductButton, selectFactoryButton;

protected:
    void keyDown(sf::Event::KeyPressed state) override;
    void mouseLClick(sf::Vector2i pos) override;
    void mouseLUnClick(sf::Vector2i pos) override;
    void mouseRClick(sf::Vector2i pos) override;
    void textInput(char32_t keyCode) override;
    void update() override;
    void draw() override;

public:
    WorkCycle(Window& window);
};
