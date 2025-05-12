#include "app.hpp"

// Realisation of base path
const std::filesystem::path resourcesDir() {
#if DEBUG
    return "../resources/";
#else
    return "resources/";
#endif
}

App::App()
: window(1024, 720, "Test window"),
cycle(window) {
    
}

App::~App() {}

void App::run() {
    cycle.run();
}
