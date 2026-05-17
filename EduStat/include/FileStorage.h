#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "Student.h"
#include <string>
#include <vector>

class FileStorage {
private:
    std::string filePath;

public:
    explicit FileStorage(const std::string& path);

    bool saveStudents(const std::vector<Student>& students) const;
    bool loadStudents(std::vector<Student>& students) const;
    bool ensureDataFileExists() const;

    std::string getFilePath() const;
    void setFilePath(const std::string& path);

private:
    Student parseStudentLine(const std::string& line) const;
    std::vector<std::string> split(const std::string& text, char delimiter) const;
};

#endif
