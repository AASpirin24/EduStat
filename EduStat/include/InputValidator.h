#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>

class InputValidator {
public:
    static bool isValidName(const std::string& value);
    static bool isValidGroup(const std::string& value);
    static bool isValidGrade(double grade);
    static bool isPositiveInteger(const std::string& value);
    static std::string trim(const std::string& value);
    static std::string toLower(std::string value);
    static bool containsIgnoreCase(const std::string& text, const std::string& query);
};

#endif
