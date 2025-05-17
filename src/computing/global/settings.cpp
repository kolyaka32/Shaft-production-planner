#include "settings.hpp"

Settings::Settings() {

}/*languageButtons {
    {920, 50, 120, 80, "GUI/Flag_ENG.png"},
    {920, 150, 120, 80, "GUI/Flag_RUS.png"},
},*/

Settings::~Settings() {
    
}

void Settings::draw(Window& window) {
    
}

bool Settings::click(sf::Vector2i pos) {
    return false;
}
/* else if (languageButtons[0].isClicked(pos)) {
    if (LanguagedText::setCurrentLanguage(Language::English)) {
        // Updating all objects
        App::restart();
    }
} else if (languageButtons[1].isClicked(pos)) {
    if (LanguagedText::setCurrentLanguage(Language::Russian)) {
        // Updating all objects
        App::restart();
    }
}*/