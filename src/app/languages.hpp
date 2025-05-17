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
    const std::string (&texts)[(unsigned)Language::Count];

public:
    LanguagedText(const std::string (&text)[(unsigned)Language::Count]);
    void setCurrentLanguage(Language newLanguage);
    std::string getString();
    sf::String getUTF8();
};
