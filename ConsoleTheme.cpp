#include "ConsoleTheme.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
#ifdef _WIN32
    WORD defaultAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    WORD toWindowsColor(ConsoleTheme::Color color) {
        switch (color) {
            case ConsoleTheme::Color::HEADER:
                return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::MENU_NUMBER:
                return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::MENU_TEXT:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            case ConsoleTheme::Color::PROMPT:
                return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::SUCCESS:
                return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::WARNING:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::ERROR_COLOR:
                return FOREGROUND_RED | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::INFO:
                return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::TABLE_HEADER:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::TABLE_LINE:
                return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::VALUE:
                return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::MUTED:
                return FOREGROUND_INTENSITY;
            case ConsoleTheme::Color::DEFAULT:
            default:
                return defaultAttributes;
        }
    }
#endif

#ifndef _WIN32
    const char* toAnsiColor(ConsoleTheme::Color color) {
        switch (color) {
            case ConsoleTheme::Color::HEADER: return "\033[96m";
            case ConsoleTheme::Color::MENU_NUMBER: return "\033[92m";
            case ConsoleTheme::Color::MENU_TEXT: return "\033[37m";
            case ConsoleTheme::Color::PROMPT: return "\033[96m";
            case ConsoleTheme::Color::SUCCESS: return "\033[92m";
            case ConsoleTheme::Color::WARNING: return "\033[93m";
            case ConsoleTheme::Color::ERROR_COLOR: return "\033[91m";
            case ConsoleTheme::Color::INFO: return "\033[94m";
            case ConsoleTheme::Color::TABLE_HEADER: return "\033[93m";
            case ConsoleTheme::Color::TABLE_LINE: return "\033[94m";
            case ConsoleTheme::Color::VALUE: return "\033[97m";
            case ConsoleTheme::Color::MUTED: return "\033[90m";
            case ConsoleTheme::Color::DEFAULT:
            default: return "\033[0m";
        }
    }
#endif
}

void ConsoleTheme::initialize() {
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (console != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(console, &info)) {
        defaultAttributes = info.wAttributes;
    }
    SetConsoleTitleW(L"Student Grades Management System");
#endif
}

void ConsoleTheme::reset() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultAttributes);
#else
    std::cout << "\033[0m";
#endif
}

void ConsoleTheme::setColor(Color color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), toWindowsColor(color));
#else
    std::cout << toAnsiColor(color);
#endif
}

void ConsoleTheme::print(Color color, const std::string& text) {
    setColor(color);
    std::cout << text;
    reset();
}

void ConsoleTheme::println(Color color, const std::string& text) {
    print(color, text + "\n");
}

void ConsoleTheme::printSeparator(char symbol, int length, Color color) {
    setColor(color);
    for (int i = 0; i < length; ++i) std::cout << symbol;
    std::cout << "\n";
    reset();
}

void ConsoleTheme::printTitle(const std::string& title) {
    std::cout << "\n";
    printSeparator('=', 60, Color::HEADER);
    int padding = static_cast<int>((60 - title.size()) / 2);
    if (padding < 0) padding = 0;
    setColor(Color::HEADER);
    for (int i = 0; i < padding; ++i) std::cout << ' ';
    std::cout << title << "\n";
    reset();
    printSeparator('=', 60, Color::HEADER);
}

void ConsoleTheme::printSuccess(const std::string& message) {
    println(Color::SUCCESS, "[OK] " + message);
}

void ConsoleTheme::printWarning(const std::string& message) {
    println(Color::WARNING, "[WARNING] " + message);
}

void ConsoleTheme::printError(const std::string& message) {
    println(Color::ERROR_COLOR, "[ERROR] " + message);
}

void ConsoleTheme::printInfo(const std::string& message) {
    println(Color::INFO, "[INFO] " + message);
}
