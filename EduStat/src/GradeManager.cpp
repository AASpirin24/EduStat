#include "GradeManager.h"
#include "InputValidator.h"
#include <algorithm>

bool GradeManager::addStudent(const Student& student) {
    if (idExists(student.getId())) return false;
    students.push_back(student);
    return true;
}

bool GradeManager::removeStudentById(int id) {
    auto originalSize = students.size();
    students.erase(std::remove_if(students.begin(), students.end(), [id](const Student& s) {
        return s.getId() == id;
    }), students.end());
    return students.size() != originalSize;
}

bool GradeManager::updateStudent(int id, const Student& updatedStudent) {
    Student* found = findStudentById(id);
    if (!found) return false;
    *found = updatedStudent;
    return true;
}

bool GradeManager::addGradeToStudent(int id, double grade) {
    Student* found = findStudentById(id);
    if (!found) return false;
    return found->addGrade(grade);
}

bool GradeManager::removeGradeFromStudent(int id, size_t index) {
    Student* found = findStudentById(id);
    if (!found) return false;
    return found->removeGrade(index);
}

bool GradeManager::updateStudentGrade(int id, size_t index, double grade) {
    Student* found = findStudentById(id);
    if (!found) return false;
    return found->updateGrade(index, grade);
}

Student* GradeManager::findStudentById(int id) {
    for (auto& student : students) {
        if (student.getId() == id) return &student;
    }
    return nullptr;
}

const Student* GradeManager::findStudentById(int id) const {
    for (const auto& student : students) {
        if (student.getId() == id) return &student;
    }
    return nullptr;
}

std::vector<Student> GradeManager::searchByName(const std::string& query) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (InputValidator::containsIgnoreCase(student.getFullName(), query)) {
            result.push_back(student);
        }
    }
    return result;
}

std::vector<Student> GradeManager::searchByGroup(const std::string& group) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (InputValidator::containsIgnoreCase(student.getGroupName(), group)) {
            result.push_back(student);
        }
    }
    return result;
}

std::vector<Student> GradeManager::searchByAverageRange(double minAvg, double maxAvg) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        double avg = student.calculateAverageRecursive();
        if (avg >= minAvg && avg <= maxAvg) result.push_back(student);
    }
    return result;
}

void GradeManager::sortStudents(SortField field, SortDirection direction) {
    auto comparator = [field, direction](const Student& a, const Student& b) {
        bool value = false;
        switch (field) {
            case SortField::ID: value = a.getId() < b.getId(); break;
            case SortField::FIRST_NAME: value = a.getFirstName() < b.getFirstName(); break;
            case SortField::LAST_NAME: value = a.getLastName() < b.getLastName(); break;
            case SortField::GROUP: value = a.getGroupName() < b.getGroupName(); break;
            case SortField::AVERAGE: value = a.calculateAverageRecursive() < b.calculateAverageRecursive(); break;
        }
        return direction == SortDirection::ASCENDING ? value : !value;
    };
    std::sort(students.begin(), students.end(), comparator);
}

std::vector<Student> GradeManager::getTopStudents(size_t count) const {
    std::vector<Student> copy = students;
    std::sort(copy.begin(), copy.end(), [](const Student& a, const Student& b) {
        return a.calculateAverageRecursive() > b.calculateAverageRecursive();
    });
    if (copy.size() > count) copy.resize(count);
    return copy;
}

std::vector<Student> GradeManager::getFailingStudents(double passingGrade) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (!student.hasPassingAverage(passingGrade)) result.push_back(student);
    }
    return result;
}

double GradeManager::calculateClassAverageRecursive() const {
    if (students.empty()) return 0.0;
    return classAverageRecursiveHelper(0, 0.0, 0);
}

double GradeManager::classAverageRecursiveHelper(size_t index, double sum, int count) const {
    if (index >= students.size()) return count == 0 ? 0.0 : sum / count;
    return classAverageRecursiveHelper(index + 1, sum + students[index].calculateAverageRecursive(), count + 1);
}

double GradeManager::calculateGroupAverageRecursive(const std::string& group) const {
    std::vector<Student> matches = searchByGroup(group);
    if (matches.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& s : matches) sum += s.calculateAverageRecursive();
    return sum / matches.size();
}

int GradeManager::generateNextId() const {
    int maxId = 0;
    for (const auto& student : students) maxId = std::max(maxId, student.getId());
    return maxId + 1;
}

bool GradeManager::idExists(int id) const {
    return findStudentById(id) != nullptr;
}

const std::vector<Student>& GradeManager::getAllStudents() const { return students; }
void GradeManager::setStudents(const std::vector<Student>& newStudents) { students = newStudents; }
void GradeManager::clear() { students.clear(); }
