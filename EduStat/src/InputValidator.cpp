#include "InputValidator.h"
#include <algorithm>
#include <cctype>

bool InputValidator::isValidName(const std::string& value) {
    std::string cleaned = trim(value);
    if (cleaned.size() < 2 || cleaned.size() > 40) return false;
    return std::all_of(cleaned.begin(), cleaned.end(), [](unsigned char c) {
        return std::isalpha(c) || c == '-' || c == '\'' || std::isspace(c);
    });
}

bool InputValidator::isValidGroup(const std::string& value) {
    std::string cleaned = trim(value);
    if (cleaned.empty() || cleaned.size() > 20) return false;
    return std::all_of(cleaned.begin(), cleaned.end(), [](unsigned char c) {
        return std::isalnum(c) || c == '-' || c == '_';
    });
}

bool InputValidator::isValidGrade(double grade) {
    return grade >= 2.0 && grade <= 6.0;
}

bool InputValidator::isPositiveInteger(const std::string& value) {
    std::string cleaned = trim(value);
    return !cleaned.empty() && std::all_of(cleaned.begin(), cleaned.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}

std::string InputValidator::trim(const std::string& value) {
    size_t start = value.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = value.find_last_not_of(" \t\n\r");
    return value.substr(start, end - start + 1);
}

std::string InputValidator::toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return value;
}

bool InputValidator::containsIgnoreCase(const std::string& text, const std::string& query) {
    return toLower(text).find(toLower(query)) != std::string::npos;
}
