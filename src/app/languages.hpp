#pragma once

#include "../testing.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Selectable languages to use
enum class Language {
    English,
    Russian,

    // Counter of all languages
    Count,

    // Standart pre-selected language
    Default = English,
};

// Class, storing one text variant in different locations
class LanguagedText {
private:
    static Language currentLanguage;
    const std::string rus, eng;

public:
    LanguagedText(const std::string engVar, const std::string rusVar);
    static bool setCurrentLanguage(Language newLanguage);
    const std::string& getString();
    sf::String getUTF8();
};
