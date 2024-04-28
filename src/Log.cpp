#include "Log.h"

void Log::Info(std::string message)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm tm;
    gmtime_s(&tm, &now_c);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    std::string timestamp = ss.str();

    std::cout << "[INFO] [" << timestamp << "] " << message << std::endl;
}

void Log::Error(std::string message)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm tm;
    gmtime_s(&tm, &now_c);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    std::string timestamp = ss.str();

    std::cout << "\033[1;31m[WARN] [" << timestamp << "] " << message << "\033[0m" << std::endl;
}
