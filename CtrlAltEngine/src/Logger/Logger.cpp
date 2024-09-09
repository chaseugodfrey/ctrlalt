#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>


std::deque<LogEntry> Logger::messages;
//https://en.cppreference.com/w/c/chrono/localtime
std::string Logger::CurrentDateTimeToString() {
    std::time_t t = std::time(nullptr);
    std::tm tm;

    localtime_s(&tm,&t);
    std::stringstream time;
        
    time.imbue(std::locale("en_US.utf-8"));
	time << std::put_time(&tm, "%c %Z") << " ";
    return time.str();
}

void Logger::LogInfo(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    std::string color = GREEN;
    logEntry.message = "[" + CurrentDateTimeToString() + "]: " + message;
    std::cout << '[' << GREENBG << "info" << RESET <<']' << logEntry.message << std::endl;
    messages.push_back(logEntry);
}