#include "Student.h"
#include <numeric>
#include <algorithm>

Student::Student() : id(0), firstName("Unknown"), lastName("Unknown"), groupName("Undefined") {}

Student::Student(int id, const std::string& firstName, const std::string& lastName, const std::string& groupName)
    : id(id), firstName(firstName), lastName(lastName), groupName(groupName) {}

int Student::getId() const { return id; }
std::string Student::getFirstName() const { return firstName; }
std::string Student::getLastName() const { return lastName; }
std::string Student::getFullName() const { return firstName + " " + lastName; }
std::string Student::getGroupName() const { return groupName; }
std::vector<double> Student::getGrades() const { return grades; }

void Student::setId(int newId) { id = newId; }
void Student::setFirstName(const std::string& name) { firstName = name; }
void Student::setLastName(const std::string& name) { lastName = name; }
void Student::setGroupName(const std::string& group) { groupName = group; }

bool Student::addGrade(double grade) {
    if (grade < 2.0 || grade > 6.0) return false;
    grades.push_back(grade);
    return true;
}

bool Student::updateGrade(size_t index, double grade) {
    if (index >= grades.size() || grade < 2.0 || grade > 6.0) return false;
    grades[index] = grade;
    return true;
}

bool Student::removeGrade(size_t index) {
    if (index >= grades.size()) return false;
    grades.erase(grades.begin() + static_cast<long>(index));
    return true;
}

void Student::clearGrades() { grades.clear(); }

double Student::calculateAverageRecursive() const {
    if (grades.empty()) return 0.0;
    return averageRecursiveHelper(0, 0.0) / grades.size();
}

double Student::averageRecursiveHelper(size_t index, double sum) const {
    if (index >= grades.size()) return sum;
    return averageRecursiveHelper(index + 1, sum + grades[index]);
}

double Student::calculateAverageIterative() const {
    if (grades.empty()) return 0.0;
    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    return sum / grades.size();
}

double Student::getMinGrade() const {
    if (grades.empty()) return 0.0;
    return *std::min_element(grades.begin(), grades.end());
}

double Student::getMaxGrade() const {
    if (grades.empty()) return 0.0;
    return *std::max_element(grades.begin(), grades.end());
}

int Student::getGradeCount() const { return static_cast<int>(grades.size()); }

bool Student::hasPassingAverage(double passingGrade) const {
    return calculateAverageRecursive() >= passingGrade;
}

std::string Student::toCsv() const {
    std::ostringstream out;
    out << id << ";" << firstName << ";" << lastName << ";" << groupName << ";";
    for (size_t i = 0; i < grades.size(); ++i) {
        out << grades[i];
        if (i + 1 < grades.size()) out << ",";
    }
    return out.str();
}

std::string Student::toDisplayString() const {
    std::ostringstream out;
    out << std::left << std::setw(5) << id
        << std::setw(16) << firstName
        << std::setw(16) << lastName
        << std::setw(12) << groupName
        << std::setw(10) << std::fixed << std::setprecision(2) << calculateAverageRecursive()
        << "Grades: ";
    if (grades.empty()) {
        out << "none";
    } else {
        for (size_t i = 0; i < grades.size(); ++i) {
            out << grades[i];
            if (i + 1 < grades.size()) out << ", ";
        }
    }
    return out.str();
}
