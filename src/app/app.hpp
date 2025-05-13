#pragma once

#include "../cycles/workCycle.hpp"


// Main process in current app
class App {
 private:
    Window window;
    WorkCycle cycle;

 public:
    App();
    ~App();
    void run();
};
