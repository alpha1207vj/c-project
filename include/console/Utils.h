#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>
#include <string>
#include <sstream>     // for ostringstream, istringstream
#include <iomanip>     // for put_time, get_time
#include <chrono>      // for system_clock, time_point
#include <ctime>       // for std::tm
class Utils {
public:
    static int lireEntier(const std::string& message);

    // Formats a system_clock::time_point to "YYYY-MM-DD"
    static std::string formatDate(const std::chrono::system_clock::time_point& tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        return oss.str();
    }

    // Parses "YYYY-MM-DD" to system_clock::time_point
    static std::chrono::system_clock::time_point parseDate(const std::string& s) {
        std::tm tm = {};
        std::istringstream ss(s);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }
};

#endif
