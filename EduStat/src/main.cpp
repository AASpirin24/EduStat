#include "Menu.h"
#include <iostream>

int main() {
    try {
        Menu menu("data/students.csv", "logs/app.log");
        menu.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
