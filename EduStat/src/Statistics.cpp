#include "Statistics.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>

static std::string formatDouble(double value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;
    return out.str();
}

double Statistics::medianAverage(std::vector<Student> students) {
    if (students.empty()) return 0.0;
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.calculateAverageRecursive() < b.calculateAverageRecursive();
    });
    size_t mid = students.size() / 2;
    if (students.size() % 2 == 0) {
        return (students[mid - 1].calculateAverageRecursive() + students[mid].calculateAverageRecursive()) / 2.0;
    }
    return students[mid].calculateAverageRecursive();
}

double Statistics::highestAverage(const std::vector<Student>& students) {
    if (students.empty()) return 0.0;
    double best = std::numeric_limits<double>::lowest();
    for (const auto& student : students) best = std::max(best, student.calculateAverageRecursive());
    return best;
}

double Statistics::lowestAverage(const std::vector<Student>& students) {
    if (students.empty()) return 0.0;
    double worst = std::numeric_limits<double>::max();
    for (const auto& student : students) worst = std::min(worst, student.calculateAverageRecursive());
    return worst;
}

GradeDistribution Statistics::buildDistribution(const std::vector<Student>& students) {
    GradeDistribution distribution;
    for (const auto& student : students) {
        double average = student.calculateAverageRecursive();
        if (average >= 5.50) distribution.excellent++;
        else if (average >= 4.50) distribution.veryGood++;
        else if (average >= 3.50) distribution.good++;
        else if (average >= 3.00) distribution.average++;
        else distribution.poor++;
    }
    return distribution;
}

std::map<std::string, double> Statistics::groupAverages(const std::vector<Student>& students) {
    std::map<std::string, double> sums;
    std::map<std::string, int> counts;
    for (const auto& student : students) {
        sums[student.getGroupName()] += student.calculateAverageRecursive();
        counts[student.getGroupName()]++;
    }

    std::map<std::string, double> averages;
    for (const auto& item : sums) {
        averages[item.first] = item.second / counts[item.first];
    }
    return averages;
}

std::string Statistics::distributionToString(const GradeDistribution& distribution) {
    std::ostringstream out;
    out << "Excellent [5.50 - 6.00]: " << distribution.excellent << "\n";
    out << "Very good [4.50 - 5.49]: " << distribution.veryGood << "\n";
    out << "Good [3.50 - 4.49]: " << distribution.good << "\n";
    out << "Average [3.00 - 3.49]: " << distribution.average << "\n";
    out << "Poor [2.00 - 2.99]: " << distribution.poor << "\n";
    return out.str();
}

std::string Statistics::groupAveragesToString(const std::map<std::string, double>& groups) {
    std::ostringstream out;
    for (const auto& group : groups) {
        out << "Group " << group.first << ": " << formatDouble(group.second) << "\n";
    }
    return out.str();
}
