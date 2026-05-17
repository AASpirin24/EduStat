#ifndef STATISTICS_H
#define STATISTICS_H

#include "Student.h"
#include <vector>
#include <map>
#include <string>

struct GradeDistribution {
    int excellent = 0;
    int veryGood = 0;
    int good = 0;
    int average = 0;
    int poor = 0;
};

class Statistics {
public:
    static double medianAverage(std::vector<Student> students);
    static double highestAverage(const std::vector<Student>& students);
    static double lowestAverage(const std::vector<Student>& students);
    static GradeDistribution buildDistribution(const std::vector<Student>& students);
    static std::map<std::string, double> groupAverages(const std::vector<Student>& students);
    static std::string distributionToString(const GradeDistribution& distribution);
    static std::string groupAveragesToString(const std::map<std::string, double>& groups);
};

#endif
