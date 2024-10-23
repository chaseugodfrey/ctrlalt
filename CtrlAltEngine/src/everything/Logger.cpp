/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "../src/pch.h"
#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include "../Editor/Editor.h"


std::vector<LogEntry> Logger::messages;
//https://en.cppreference.com/w/c/chrono/localtime 
/**
 * @brief Get the current date and time as a string
 * @return std::string The current date and time as a string
 * 
 */
std::string Logger::CurrentDateTimeToString() {
    std::time_t t = std::time(nullptr);
    std::tm tm;

    localtime_s(&tm,&t);
    std::stringstream time;
        
    time.imbue(std::locale("en_US.utf-8"));
	time << std::put_time(&tm, "%c %Z") << " ";
    return time.str();
}

/**
 * @brief Log a message with a severity level of INFO
 * @param message The message to log
 */
void Logger::LogInfo(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    std::string color = GREEN;
    logEntry.message = "[" + CurrentDateTimeToString() + "]: " + message;
    std::cout << '[' << GREEN << "info" << RESET <<']' << logEntry.message << std::endl;

    //Editor::GetEditor()->ConsoleAddLine(logEntry.message);

    messages.push_back(logEntry);
}