#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
private:
    std::string logPath;

public:
    explicit Logger(const std::string& path);
    void info(const std::string& message) const;
    void warning(const std::string& message) const;
    void error(const std::string& message) const;

private:
    void write(const std::string& level, const std::string& message) const;
    std::string currentDateTime() const;
};

#endif
