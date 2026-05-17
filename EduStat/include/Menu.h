#ifndef MENU_H
#define MENU_H

#include "GradeManager.h"
#include "FileStorage.h"
#include "Logger.h"

class Menu {
private:
    GradeManager manager;
    FileStorage storage;
    Logger logger;

public:
    Menu(const std::string& dataPath, const std::string& logPath);
    void run();

private:
    void printMainMenu() const;
    void handleChoice(int choice);
    void loadData();
    void saveData();
    void addStudent();
    void listStudents() const;
    void searchStudents() const;
    void sortStudents();
    void editStudent();
    void deleteStudent();
    void showStatistics() const;
    void seedSampleData();

    int readInteger(const std::string& prompt) const;
    double readDouble(const std::string& prompt) const;
    std::string readLine(const std::string& prompt) const;
    void waitForEnter() const;
};

#endif
