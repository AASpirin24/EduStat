#include "Menu.h"
#include "InputValidator.h"
#include "Statistics.h"
#include "ConsoleTheme.h"
#include <iostream>
#include <limits>
#include <iomanip>

Menu::Menu(const std::string& dataPath, const std::string& logPath)
    : storage(dataPath), logger(logPath) {}

void Menu::run() {
    ConsoleTheme::initialize();
    storage.ensureDataFileExists();
    loadData();

    bool running = true;
    while (running) {
        printMainMenu();
        int choice = readInteger("Choose an option: ");
        if (choice == 0) {
            saveData();
            running = false;
        } else {
            handleChoice(choice);
        }
    }
    ConsoleTheme::printSuccess("Goodbye! Data has been saved.");
}

void Menu::printMainMenu() const {
    ConsoleTheme::printTitle("STUDENT GRADES MANAGEMENT SYSTEM");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 1. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Load data from file");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 2. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Save data to file");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 3. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Add new student");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 4. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "List all students");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 5. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Search students");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 6. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Sort students");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 7. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Edit student and grades");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 8. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Delete student");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, " 9. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Show statistics");
    ConsoleTheme::print(ConsoleTheme::Color::MENU_NUMBER, "10. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Insert sample data");
    ConsoleTheme::print(ConsoleTheme::Color::ERROR_COLOR,       " 0. "); ConsoleTheme::println(ConsoleTheme::Color::MENU_TEXT, "Save and exit");
    ConsoleTheme::printSeparator('=', 60, ConsoleTheme::Color::HEADER);
}

void Menu::handleChoice(int choice) {
    switch (choice) {
        case 1: loadData(); break;
        case 2: saveData(); break;
        case 3: addStudent(); break;
        case 4: listStudents(); break;
        case 5: searchStudents(); break;
        case 6: sortStudents(); break;
        case 7: editStudent(); break;
        case 8: deleteStudent(); break;
        case 9: showStatistics(); break;
        case 10: seedSampleData(); break;
        default: ConsoleTheme::printError("Invalid option. Try again."); break;
    }
}

void Menu::loadData() {
    std::vector<Student> loaded;
    if (storage.loadStudents(loaded)) {
        manager.setStudents(loaded);
        logger.info("Data loaded from file.");
        ConsoleTheme::printSuccess("Loaded " + std::to_string(loaded.size()) + " students.");
    } else {
        logger.warning("Could not load data file.");
        ConsoleTheme::printWarning("Could not load data file. Starting with empty list.");
    }
}

void Menu::saveData() {
    if (storage.saveStudents(manager.getAllStudents())) {
        logger.info("Data saved to file.");
        ConsoleTheme::printSuccess("Data saved successfully.");
    } else {
        logger.error("Could not save data file.");
        ConsoleTheme::printError("Could not save data.");
    }
}

void Menu::addStudent() {
    int id = manager.generateNextId();
    std::string firstName;
    std::string lastName;
    std::string group;

    do { firstName = readLine("First name: "); } while (!InputValidator::isValidName(firstName));
    do { lastName = readLine("Last name: "); } while (!InputValidator::isValidName(lastName));
    do { group = readLine("Group: "); } while (!InputValidator::isValidGroup(group));

    Student student(id, firstName, lastName, group);
    int gradeCount = readInteger("How many grades should be entered? ");
    for (int i = 0; i < gradeCount; ++i) {
        double grade = readDouble("Grade " + std::to_string(i + 1) + " [2.00 - 6.00]: ");
        if (!student.addGrade(grade)) {
            ConsoleTheme::printError("Invalid grade. Repeating this input.");
            --i;
        }
    }

    if (manager.addStudent(student)) {
        logger.info("Student added: " + student.getFullName());
        ConsoleTheme::printSuccess("Student added with ID " + std::to_string(id) + ".");
    } else {
        logger.error("Could not add student because ID already exists.");
        ConsoleTheme::printError("Could not add student.");
    }
}

void Menu::listStudents() const {
    const auto& students = manager.getAllStudents();
    if (students.empty()) {
        ConsoleTheme::printWarning("No students available.");
        return;
    }

    ConsoleTheme::setColor(ConsoleTheme::Color::TABLE_HEADER);
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(16) << "First name"
              << std::setw(16) << "Last name"
              << std::setw(12) << "Group"
              << std::setw(10) << "Average"
              << "Grades\n";
    ConsoleTheme::reset();
    ConsoleTheme::printSeparator('-', 85, ConsoleTheme::Color::TABLE_LINE);
    for (const auto& student : students) std::cout << student.toDisplayString() << "\n";
}

void Menu::searchStudents() const {
    std::cout << "1. Search by name\n2. Search by group\n3. Search by average range\n";
    int option = readInteger("Search option: ");
    std::vector<Student> result;

    if (option == 1) {
        std::string query = readLine("Name query: ");
        result = manager.searchByName(query);
    } else if (option == 2) {
        std::string group = readLine("Group query: ");
        result = manager.searchByGroup(group);
    } else if (option == 3) {
        double minAvg = readDouble("Minimum average: ");
        double maxAvg = readDouble("Maximum average: ");
        result = manager.searchByAverageRange(minAvg, maxAvg);
    } else {
        ConsoleTheme::printError("Invalid search option.");
        return;
    }

    if (result.empty()) {
        ConsoleTheme::printWarning("No matching students found.");
        return;
    }
    for (const auto& student : result) std::cout << student.toDisplayString() << "\n";
}

void Menu::sortStudents() {
    std::cout << "Sort by: 1-ID 2-First name 3-Last name 4-Group 5-Average\n";
    int fieldChoice = readInteger("Field: ");
    std::cout << "Direction: 1-Ascending 2-Descending\n";
    int directionChoice = readInteger("Direction: ");

    SortField field = SortField::ID;
    if (fieldChoice == 2) field = SortField::FIRST_NAME;
    else if (fieldChoice == 3) field = SortField::LAST_NAME;
    else if (fieldChoice == 4) field = SortField::GROUP;
    else if (fieldChoice == 5) field = SortField::AVERAGE;

    SortDirection direction = directionChoice == 2 ? SortDirection::DESCENDING : SortDirection::ASCENDING;
    manager.sortStudents(field, direction);
    logger.info("Students sorted.");
    ConsoleTheme::printSuccess("Students sorted successfully.");
}

void Menu::editStudent() {
    int id = readInteger("Student ID to edit: ");
    Student* student = manager.findStudentById(id);
    if (!student) {
        ConsoleTheme::printError("Student not found.");
        return;
    }

    std::cout << "Editing: " << student->toDisplayString() << "\n";
    std::cout << "1. Change name\n2. Change group\n3. Add grade\n4. Update grade\n5. Remove grade\n6. Clear all grades\n";
    int option = readInteger("Edit option: ");

    if (option == 1) {
        std::string first = readLine("New first name: ");
        std::string last = readLine("New last name: ");
        if (InputValidator::isValidName(first) && InputValidator::isValidName(last)) {
            student->setFirstName(first);
            student->setLastName(last);
        }
    } else if (option == 2) {
        std::string group = readLine("New group: ");
        if (InputValidator::isValidGroup(group)) student->setGroupName(group);
    } else if (option == 3) {
        double grade = readDouble("New grade: ");
        if (!student->addGrade(grade)) ConsoleTheme::printError("Invalid grade.");
    } else if (option == 4) {
        int index = readInteger("Grade index starting from 1: ") - 1;
        double grade = readDouble("New grade: ");
        if (!student->updateGrade(static_cast<size_t>(index), grade)) ConsoleTheme::printError("Could not update grade.");
    } else if (option == 5) {
        int index = readInteger("Grade index starting from 1: ") - 1;
        if (!student->removeGrade(static_cast<size_t>(index))) ConsoleTheme::printError("Could not remove grade.");
    } else if (option == 6) {
        student->clearGrades();
    } else {
        ConsoleTheme::printError("Invalid edit option.");
    }
    logger.info("Student edited: ID " + std::to_string(id));
}

void Menu::deleteStudent() {
    int id = readInteger("Student ID to delete: ");
    if (manager.removeStudentById(id)) {
        logger.info("Student deleted: ID " + std::to_string(id));
        ConsoleTheme::printSuccess("Student deleted.");
    } else {
        ConsoleTheme::printError("Student not found.");
    }
}

void Menu::showStatistics() const {
    const auto& students = manager.getAllStudents();
    ConsoleTheme::printTitle("STATISTICS");

    ConsoleTheme::print(ConsoleTheme::Color::INFO, "Students count: ");
    ConsoleTheme::println(ConsoleTheme::Color::VALUE, std::to_string(students.size()));

    ConsoleTheme::print(ConsoleTheme::Color::INFO, "Class average recursive: ");
    ConsoleTheme::setColor(ConsoleTheme::Color::VALUE);
    std::cout << std::fixed << std::setprecision(2) << manager.calculateClassAverageRecursive() << "\n";
    ConsoleTheme::reset();

    ConsoleTheme::print(ConsoleTheme::Color::INFO, "Median average: ");
    ConsoleTheme::setColor(ConsoleTheme::Color::VALUE);
    std::cout << Statistics::medianAverage(students) << "\n";
    ConsoleTheme::reset();

    ConsoleTheme::print(ConsoleTheme::Color::INFO, "Highest average: ");
    ConsoleTheme::setColor(ConsoleTheme::Color::VALUE);
    std::cout << Statistics::highestAverage(students) << "\n";
    ConsoleTheme::reset();

    ConsoleTheme::print(ConsoleTheme::Color::INFO, "Lowest average: ");
    ConsoleTheme::setColor(ConsoleTheme::Color::VALUE);
    std::cout << Statistics::lowestAverage(students) << "\n\n";
    ConsoleTheme::reset();

    ConsoleTheme::println(ConsoleTheme::Color::TABLE_HEADER, "Distribution:");
    std::cout << Statistics::distributionToString(Statistics::buildDistribution(students));

    ConsoleTheme::println(ConsoleTheme::Color::TABLE_HEADER, "\nGroup averages:");
    std::cout << Statistics::groupAveragesToString(Statistics::groupAverages(students));

    auto top = manager.getTopStudents(3);
    ConsoleTheme::println(ConsoleTheme::Color::TABLE_HEADER, "\nTop students:");
    for (const auto& student : top) std::cout << student.toDisplayString() << "\n";
}

void Menu::seedSampleData() {
    Student a(manager.generateNextId(), "Emily", "Johnson", "CS-101");
    a.addGrade(6.0); a.addGrade(5.75); a.addGrade(5.50);
    manager.addStudent(a);

    Student b(manager.generateNextId(), "Michael", "Brown", "CS-101");
    b.addGrade(4.50); b.addGrade(5.00); b.addGrade(4.75);
    manager.addStudent(b);

    Student c(manager.generateNextId(), "Sophia", "Davis", "IT-202");
    c.addGrade(3.25); c.addGrade(3.50); c.addGrade(4.00);
    manager.addStudent(c);

    Student d(manager.generateNextId(), "Daniel", "Wilson", "IT-202");
    d.addGrade(2.50); d.addGrade(2.75); d.addGrade(3.00);
    manager.addStudent(d);

    logger.info("Sample data inserted.");
    ConsoleTheme::printSuccess("Sample data inserted.");
}

int Menu::readInteger(const std::string& prompt) const {
    int value;
    while (true) {
        ConsoleTheme::print(ConsoleTheme::Color::PROMPT, prompt);
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ConsoleTheme::printError("Invalid integer. Try again.");
    }
}

double Menu::readDouble(const std::string& prompt) const {
    double value;
    while (true) {
        ConsoleTheme::print(ConsoleTheme::Color::PROMPT, prompt);
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ConsoleTheme::printError("Invalid number. Try again.");
    }
}

std::string Menu::readLine(const std::string& prompt) const {
    std::string value;
    ConsoleTheme::print(ConsoleTheme::Color::PROMPT, prompt);
    std::getline(std::cin, value);
    return InputValidator::trim(value);
}

void Menu::waitForEnter() const {
    ConsoleTheme::print(ConsoleTheme::Color::PROMPT, "Press Enter to continue...");
    std::cin.get();
}
