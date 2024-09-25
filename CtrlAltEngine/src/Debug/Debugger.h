/**
@group CTRL ALT
@file Debugger.h
@brief Debugging information to be calculated here
Created by Jerron Teng
t.junrongjerron@digipen.edu
*/ 

#pragma once 
#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "thread" //Simulated workload for FPS
#include <iostream>
#include <string>
#include <cmath> //Find approximate


namespace Debug {

        void fpsUpdate(std::string *fps_string);
}
#endif