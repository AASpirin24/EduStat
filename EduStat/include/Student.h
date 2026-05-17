#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class Student {
private:
    int id;
    std::string firstName;
    std::string lastName;
    std::string groupName;
    std::vector<double> grades;

public:
    Student();
    Student(int id, const std::string& firstName, const std::string& lastName, const std::string& groupName);

    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    std::string getGroupName() const;
    std::vector<double> getGrades() const;

    void setId(int newId);
    void setFirstName(const std::string& name);
    void setLastName(const std::string& name);
    void setGroupName(const std::string& group);

    bool addGrade(double grade);
    bool updateGrade(size_t index, double grade);
    bool removeGrade(size_t index);
    void clearGrades();

    double calculateAverageRecursive() const;
    double calculateAverageIterative() const;
    double getMinGrade() const;
    double getMaxGrade() const;
    int getGradeCount() const;
    bool hasPassingAverage(double passingGrade = 3.0) const;

    std::string toCsv() const;
    std::string toDisplayString() const;

private:
    double averageRecursiveHelper(size_t index, double sum) const;
};

#endif
