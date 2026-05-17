#include "Logger.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger(const std::string& path) : logPath(path) {}

void Logger::info(const std::string& message) const { write("INFO", message); }
void Logger::warning(const std::string& message) const { write("WARNING", message); }
void Logger::error(const std::string& message) const { write("ERROR", message); }

void Logger::write(const std::string& level, const std::string& message) const {
    std::ofstream file(logPath, std::ios::app);
    if (!file.is_open()) return;
    file << "[" << currentDateTime() << "] [" << level << "] " << message << "\n";
}

std::string Logger::currentDateTime() const {
    auto now = std::chrono::system_clock::now();
    std::time_t rawTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &rawTime);
#else
    localtime_r(&rawTime, &localTime);
#endif

    std::ostringstream out;
    out << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return out.str();
}
