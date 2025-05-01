#include "app.hpp"


App::App()
: window(1024, 720, "Test window"),
cycle(window) {
    
}

App::~App() {

}

void App::run() {
    cycle.run();
}
