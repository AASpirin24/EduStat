#include "FileStorage.h"
#include <fstream>
#include <sstream>
#include <filesystem>

FileStorage::FileStorage(const std::string& path) : filePath(path) {}

bool FileStorage::saveStudents(const std::vector<Student>& students) const {
    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    file << "id;first_name;last_name;group;grades\n";
    for (const auto& student : students) {
        file << student.toCsv() << "\n";
    }
    return true;
}

bool FileStorage::loadStudents(std::vector<Student>& students) const {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    students.clear();
    std::string line;
    bool headerSkipped = false;

    while (std::getline(file, line)) {
        if (!headerSkipped) {
            headerSkipped = true;
            continue;
        }
        if (!line.empty()) students.push_back(parseStudentLine(line));
    }
    return true;
}

bool FileStorage::ensureDataFileExists() const {
    std::filesystem::path path(filePath);
    if (std::filesystem::exists(path)) return true;
    std::filesystem::create_directories(path.parent_path());
    std::ofstream file(filePath);
    if (!file.is_open()) return false;
    file << "id;first_name;last_name;group;grades\n";
    return true;
}

std::string FileStorage::getFilePath() const { return filePath; }
void FileStorage::setFilePath(const std::string& path) { filePath = path; }

Student FileStorage::parseStudentLine(const std::string& line) const {
    std::vector<std::string> parts = split(line, ';');
    if (parts.size() < 4) return Student();

    Student student(std::stoi(parts[0]), parts[1], parts[2], parts[3]);
    if (parts.size() >= 5 && !parts[4].empty()) {
        std::vector<std::string> gradeParts = split(parts[4], ',');
        for (const auto& gradeText : gradeParts) {
            try {
                student.addGrade(std::stod(gradeText));
            } catch (...) {
                // Invalid grade fields are ignored so the rest of the file can still be loaded.
            }
        }
    }
    return student;
}

std::vector<std::string> FileStorage::split(const std::string& text, char delimiter) const {
    std::vector<std::string> result;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delimiter)) result.push_back(item);
    return result;
}
