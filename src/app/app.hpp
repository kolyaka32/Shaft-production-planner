#pragma once

#include "../workCycle.hpp"

class App {
 private:
    Window window;
    WorkCycle cycle;

 public:
    App();
    ~App();
    void run();
};
