#ifndef GRADE_MANAGER_H
#define GRADE_MANAGER_H

#include "Student.h"
#include <vector>
#include <string>
#include <optional>

enum class SortField {
    ID,
    FIRST_NAME,
    LAST_NAME,
    GROUP,
    AVERAGE
};

enum class SortDirection {
    ASCENDING,
    DESCENDING
};

class GradeManager {
private:
    std::vector<Student> students;

public:
    bool addStudent(const Student& student);
    bool removeStudentById(int id);
    bool updateStudent(int id, const Student& updatedStudent);
    bool addGradeToStudent(int id, double grade);
    bool removeGradeFromStudent(int id, size_t index);
    bool updateStudentGrade(int id, size_t index, double grade);

    Student* findStudentById(int id);
    const Student* findStudentById(int id) const;
    std::vector<Student> searchByName(const std::string& query) const;
    std::vector<Student> searchByGroup(const std::string& group) const;
    std::vector<Student> searchByAverageRange(double minAvg, double maxAvg) const;

    void sortStudents(SortField field, SortDirection direction);
    std::vector<Student> getTopStudents(size_t count) const;
    std::vector<Student> getFailingStudents(double passingGrade = 3.0) const;

    double calculateClassAverageRecursive() const;
    double calculateGroupAverageRecursive(const std::string& group) const;
    int generateNextId() const;
    bool idExists(int id) const;

    const std::vector<Student>& getAllStudents() const;
    void setStudents(const std::vector<Student>& newStudents);
    void clear();

private:
    double classAverageRecursiveHelper(size_t index, double sum, int count) const;
};

#endif
