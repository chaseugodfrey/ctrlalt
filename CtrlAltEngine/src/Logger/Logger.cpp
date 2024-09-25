/**
@group CTRL ALT
@file Logger.cpp
@brief Implementation of simple Logging system
Created by Michael Lazaroo
m.lazaroo@digipen.edu
*/

#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>


std::vector<LogEntry> Logger::messages;
auto endFrameTime = std::chrono::high_resolution_clock::now(); //Tracker for FPS, init with value first so auto knows the type
int framecount = 0; //Counter for FPS
std::chrono::duration<double> elapsedDurationBetweenFrames = endFrameTime - endFrameTime;

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

void Logger::LogMessage(const Severity sevLevel, const std::string& message) {
    LogEntry logEntry;
    std::string logType = "";
    logEntry.type = sevLevel;
    std::string color = GREEN;
    switch (logEntry.type) {
    case 0:
        logType = "Info";
        color = BLUE;
        break;
    case 1:
        logType = "Warning";
        color = RED;
        break;
    case 2:
        logType = "Error";
        color = RED;
        break;
    case 3:
        logType = "Success";
        color = GREEN;
        break;
    }
    logEntry.message = "[" + CurrentDateTimeToString() + "]: " + message;
    std::cout << '[' << color << logType << RESET <<']' << logEntry.message << std::endl;
    messages.push_back(logEntry);
}