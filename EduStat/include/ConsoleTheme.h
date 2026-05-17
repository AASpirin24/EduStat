#ifndef CONSOLE_THEME_H
#define CONSOLE_THEME_H

#include <iostream>
#include <string>

class ConsoleTheme {
public:
    enum class Color {
        DEFAULT,
        HEADER,
        MENU_NUMBER,
        MENU_TEXT,
        PROMPT,
        SUCCESS,
        WARNING,
        ERROR_COLOR,
        INFO,
        TABLE_HEADER,
        TABLE_LINE,
        VALUE,
        MUTED
    };

    static void initialize();
    static void reset();
    static void setColor(Color color);
    static void print(Color color, const std::string& text);
    static void println(Color color, const std::string& text);
    static void printSeparator(char symbol = '=', int length = 60, Color color = Color::TABLE_LINE);
    static void printTitle(const std::string& title);
    static void printSuccess(const std::string& message);
    static void printWarning(const std::string& message);
    static void printError(const std::string& message);
    static void printInfo(const std::string& message);
};

#endif
