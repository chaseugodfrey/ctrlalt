/**
@group CTRL ALT
@file Logger.h
@brief Implementation of simple Logging system
Created by Michael Lazaroo
m.lazaroo@digipen.edu
*/

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
//Jerron's Includes
#include "thread" //Simulated workload for FPS
#include <string>
#include <cmath> //Find approximate
//End of Jerron's Includes



constexpr const char* GREEN = "\033[32m";
constexpr const char* GREENBG = "\033[42m";
constexpr const char* RED = "\033[31m";
constexpr const char* REDBG = "\033[41m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* BLUEBG = "\033[44m";
constexpr const char* RESET = "\033[0m";
//https://en.wikipedia.org/wiki/ANSI_escape_code#Colors have fun
constexpr const char* LOG_INFO_COLOR = GREEN;

typedef enum{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_SUCCESS
} Severity;

class LogEntry {
public:
    Severity type;
    std::string message;
};

class Logger {

public:
    static void LogMessage(const Severity sevLevel,const std::string& message);
    static std::vector<LogEntry> messages;
private:
    static std::string CurrentDateTimeToString();
};

#endif

