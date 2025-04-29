#include "app.hpp"


App::App()
: window(800, 600, "Test window"),
cycle(window) {
    
}

App::~App() {

}

void App::run() {
    cycle.run(window);
}
