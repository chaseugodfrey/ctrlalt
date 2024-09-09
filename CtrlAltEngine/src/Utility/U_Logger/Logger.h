#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <deque>


namespace Utility {

    constexpr const char* GREENBG = "\033[42m";
	constexpr const char* GREEN = "\033[32m";
	constexpr const char* REDBG = "\033[41m";
	constexpr const char* RESET = "\033[0m";
    //https://en.wikipedia.org/wiki/ANSI_escape_code#Colors have fun
    constexpr const char* LOG_INFO_COLOR = GREEN;

    enum Severity :uint8_t {
        LOG_INFO
    };

    class LogEntry {
    public:
        Severity type;
        std::string message;
    };

    class Logger {

    public:
        static void LogInfo(const std::string& message);
        static std::deque<LogEntry> messages;
    private:
        static std::string CurrentDateTimeToString();
    };
    }
#endif

