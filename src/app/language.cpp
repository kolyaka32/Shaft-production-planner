#include "languages.hpp"

// Static class member
Language LanguagedText::currentLanguage = Language::Default;


LanguagedText::LanguagedText(const std::string (&_texts)[(unsigned)Language::Count])
: texts(_texts) {}

void LanguagedText::setCurrentLanguage(Language newLanguage) {
    currentLanguage = newLanguage;
}

std::string LanguagedText::getString() {
    return texts[(unsigned)currentLanguage];
}

sf::String LanguagedText::getUTF8() {
    return sf::String::fromUtf8(getString().begin(), getString().end());
}
